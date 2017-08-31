//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//
// Copyright (c) 2015-2017, Lawrence Livermore National Security, LLC.
// 
// Produced at the Lawrence Livermore National Laboratory
// 
// LLNL-CODE-716457
// 
// All rights reserved.
// 
// This file is part of Alpine. 
// 
// For details, see: http://software.llnl.gov/alpine/.
// 
// Please also read alpine/LICENSE
// 
// Redistribution and use in source and binary forms, with or without 
// modification, are permitted provided that the following conditions are met:
// 
// * Redistributions of source code must retain the above copyright notice, 
//   this list of conditions and the disclaimer below.
// 
// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the disclaimer (as noted below) in the
//   documentation and/or other materials provided with the distribution.
// 
// * Neither the name of the LLNS/LLNL nor the names of its contributors may
//   be used to endorse or promote products derived from this software without
//   specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL LAWRENCE LIVERMORE NATIONAL SECURITY,
// LLC, THE U.S. DEPARTMENT OF ENERGY OR CONTRIBUTORS BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL 
// DAMAGES  (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
// OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
// HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, 
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
// IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
// POSSIBILITY OF SUCH DAMAGE.
// 
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~//


//-----------------------------------------------------------------------------
///
/// file: alpine_blueprint_hdf5_pipeline.cpp
///
//-----------------------------------------------------------------------------

#include <adios.h>
#include <adios_types.h>
#include "alpine_adios_pipeline.hpp"
#include <alpine_file_system.hpp>

// standard lib includes
#include <iostream>
#include <string.h>
#include <limits.h>
#include <cstdlib>

//-----------------------------------------------------------------------------
// thirdparty includes
//-----------------------------------------------------------------------------

// conduit includes
#include <conduit_relay.hpp>
#include <conduit_blueprint.hpp>

// mpi related includes
#ifdef PARALLEL
#include <mpi.h>
// -- conduit relay mpi
#include <conduit_relay_mpi.hpp>
#endif

#include <sstream>

using namespace conduit;
using namespace conduit::relay;

using namespace std;


//-----------------------------------------------------------------------------
// -- begin alpine:: --
//-----------------------------------------------------------------------------
namespace alpine
{

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// Internal Class that coordinates writing.
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
class AdiosPipeline::IOManager
{
public:

    // construction and destruction 
#ifdef PARALLEL
     IOManager(MPI_Comm mpi_comm);
#else
     IOManager();
#endif
    ~IOManager();

    // main call to create adios file set
    void SaveToAdiosFormat(const Node &data, const Node &options);

//-----------------------------------------------------------------------------
// private vars for MPI case
//-----------------------------------------------------------------------------
private:
    int m_rank;
    int64_t 	m_adios_group;
    int64_t	m_adios_file;

//-----------------------------------------------------------------------------
// private vars for MPI case
//-----------------------------------------------------------------------------
#ifdef PARALLEL
    MPI_Comm            m_mpi_comm;
    int                 m_mpi_size;
#endif 

};

#ifdef PARALLEL
//-----------------------------------------------------------------------------
AdiosPipeline::IOManager::IOManager(MPI_Comm mpi_comm)
:m_rank(0),
 m_mpi_comm(mpi_comm)
{
    MPI_Comm_rank(m_mpi_comm, &m_rank);
    MPI_Comm_size(m_mpi_comm, &m_mpi_size);
}
#else
//-----------------------------------------------------------------------------
AdiosPipeline::IOManager::IOManager()
:m_rank(0)
{
    
}
#endif


//-----------------------------------------------------------------------------
AdiosPipeline::IOManager::~IOManager()
{
    // empty
}

//-----------------------------------------------------------------------------
void
AdiosPipeline::IOManager::SaveToAdiosFormat(const Node &data, const Node &options)
{
#ifdef PARALLEL
    adios_init_noxml (m_mpi_comm);
    adios_set_max_buffer_size (10);

    int par_size;
    MPI_Comm_size(m_mpi_comm, &par_size);
    adios_declare_group (&m_adios_group,"test_data", "iter", adios_stat_default);
    //adios_select_method (m_adios_group, "DATASPACES", "", "");
    adios_select_method (m_adios_group, "MPI", "", "");
   
    
    
    char        filename [100];    
    strcpy (filename, options["output_path"].as_char8_str());
    adios_open (&m_adios_file, "test_data", filename, "w", m_mpi_comm);
    adios_define_schema_version(m_adios_group, "1.1"); 
    std::string var_mesh = "";
    cout << "rank " << m_rank << endl;

    //Spacing, dims, orig are local
    char spacing[3] = "";
    string space;
    char dims[3] = "";
    char orig[3] = "";

    //global dim & g_dim and global origin & g_origin are global
    char global_dim[3] = "";
    char global_origin[3] = "";
    int g_dim[3];
    double g_origin[3]; 

    //space mesh, local origin, and local dim are local, correspond to the local char arrays above. 
    double space_mesh[3];
    double local_origin[3];
    int local_dim[3];

    //max dim is used to find the global dimensions
    int max_dim[3]; //local dim + local origin then mpi reduction to find max among ranks


    NodeConstIterator itr = data["coordsets"].children();
    while(itr.has_next()){
         const Node &coordset = itr.next();
         std::string coordset_name = itr.name();
         std::string coordset_type = coordset["type"].as_string();
         if(coordset_type == "uniform"){
                if(coordset.has_child("spacing")){
                        NodeConstIterator space_itr = coordset["spacing"].children();
                        int i = 0;
                        while(space_itr.has_next()){
                                const Node &space = space_itr.next();
                                double s = space.as_float64();
                                space_mesh[i++] = s;
                        }
                        //sprintf(spacing, "%.04f,%.04f,%.04f", space_mesh[0],space_mesh[1],space_mesh[2]);
                        stringstream ss;
                	space = ss.str();
		}
                if(coordset.has_child("origin")){
                        NodeConstIterator origin_itr = coordset["origin"].children();
                        int i = 0;
                        while(origin_itr.has_next()){
                                const Node &origin = origin_itr.next();
                                double o = origin.as_float64();
                                local_origin[i] = o/space_mesh[i];
 				i++;
                        }
			MPI_Reduce(local_origin,g_origin,3, MPI_DOUBLE,MPI_MIN,0,MPI_COMM_WORLD);
			if(m_rank == 0){ 
                        	sprintf(global_origin, "%d,%d,%d", (int)g_origin[0], (int)g_origin[1], (int)g_origin[2]);
                        	//sprintf(global_origin, "%f,%f,%f", g_origin[0], g_origin[1], g_origin[2]);
			}
			sprintf(orig, "%d,%d,%d", (int)local_origin[0],(int)local_origin[1],(int)local_origin[2]);
			//sprintf(orig, "%f,%f,%f", local_origin[0],local_origin[1],local_origin[2]);
              }
              if(coordset.has_child("dims")){
                        NodeConstIterator dim_itr = coordset["dims"].children();
                        int i = 0;
                        while(dim_itr.has_next()){
                                const Node &dim = dim_itr.next();
                                int d = dim.as_int32();
				max_dim[i] = d + (int)local_origin[i];
                                local_dim[i++] = d;
               //                 cout << "dim " << d << endl;
                        }
                        sprintf(dims, "%d,%d,%d", local_dim[0],local_dim[1],local_dim[2]);
			MPI_Allreduce(max_dim,g_dim,3, MPI_INT,MPI_MAX,MPI_COMM_WORLD);
                	sprintf(global_dim, "%d,%d,%d", g_dim[0], g_dim[1], g_dim[2]);
		}
                std::string type = "uniformmesh";
                var_mesh = type;
		if(m_rank == 0){
			cout << "defining uniform mesh" << endl;
			cout << "mesh dimensions: " << global_dim << endl;
			cout << "mesh origin: " << global_origin << endl;
			cout << "mesh spacing: " << space << endl;
			char *sp = new char[space.length() + 1];
			strcpy(sp, space.c_str());
                	adios_define_mesh_uniform(global_dim, global_origin, sp, 0, "3", m_adios_group, "uniformmesh");
                	adios_define_mesh_timevarying ("no", m_adios_group, type.c_str());
		}
        //	adios_define_attribute(m_adios_group, "mesh", "", adios_string, "uniformmesh","");
        }
        else if(coordset_type == "rectilinear"){
                NodeConstIterator values_itr = coordset["values"].children();
                 while(values_itr.has_next()){
                        const Node &coords_values = values_itr.next();
                        char var_name[50]="";
                        DataType x_dt=coords_values.dtype();
                        int num_ele=x_dt.number_of_elements();
                        int ele_size=x_dt.element_bytes();
                        std::string c = itr.name();
                        std::string var = values_itr.name();
                        sprintf(var_name,"coords_%s", var.c_str());
                        //int64_t var_id = adios_define_var (m_adios_group, var_name,"", adios_double, l_str,g_str,o_str);
                        //adios_set_transform (var_id, "none");
                        //adios_write_byid(m_adios_file, var_id, (void *)coords_values.as_float64_ptr());
                }
               //TODO: Global dimensions 
              if(coordset.has_child("dims")){
                        NodeConstIterator dim_itr = coordset["dims"].children();
                        int i = 0;
                        while(dim_itr.has_next()){
                                const Node &dim = dim_itr.next();
                                double d = dim.as_int32();
				local_dim[i++] = d;
                        }
                        sprintf(dims, "%d,%d,%d", local_dim[0],local_dim[1],local_dim[2]);
		}
                else{   
                        ;//sprintf(dims, "%d,%d,%d", options["dim"].as_int32(),options["dim"].as_int32(),options["dim"].as_int32());
                }
                std::string type = "rectilinearmesh";
                var_mesh = type;
                adios_define_mesh_timevarying ("no", m_adios_group, type.c_str());
                std::string coordinates = "xd";
                adios_define_mesh_rectilinear(dims, "coords_x,coords_y,coords_z", 0, m_adios_group, type.c_str());
         }
         else   
                std::cout << "coordset type " << coordset_type <<std::endl;
    }
    if(data.has_child("fields")){
        string field_name = options["field_name"].as_string();
        const Node &fld = data["fields"][field_name];
        if (fld.has_child("values")){
                    const Node &fld_val = fld["values"];
                    char var_name[50]="";
                    DataType v_dt=fld_val.dtype();
                    int num_ele=v_dt.number_of_elements();
                    //std::cout << "n ele " << num_ele << std::endl;
                    int ele_size=v_dt.element_bytes();
                    std::string var = itr.name();
                    sprintf(var_name,"field_%s", var.c_str());
                    //std::cout<<g_str<<" vbn "<<l_str<<"  "<<o_str<<"  "<< m_rank<<"\n";
                    int64_t var_id = adios_define_var (m_adios_group, field_name.c_str(),"", adios_double, dims ,global_dim, orig);
                    cout << "rank: " << m_rank << " l di: " << dims << " g dim: " << global_dim << " orig/offset: " << orig << endl;
			adios_define_attribute(m_adios_group, "field_name", "", adios_string, field_name.c_str(),"");
                    adios_define_var_mesh(m_adios_group, field_name.c_str(),var_mesh.c_str());
                    if(fld.has_child("association")){
                        std::string association = fld["association"].as_string();
                        if(association == "vertex"){
                                std::string assoc = "point";
                                adios_define_var_centering(m_adios_group, field_name.c_str(), assoc.c_str());
                        }
                        else{
                                std::string assoc = "cell";
                                adios_define_var_centering(m_adios_group, field_name.c_str(), assoc.c_str());
                        }               
                    }
                    //adios_set_transform (var_id, "none");
                    adios_write(m_adios_file, field_name.c_str(), (void *)fld_val.as_float64_ptr());
	}

    }
/*
    if (data.has_child("fields")){
        itr = data["fields"].children();
        int j = 0;
        while(itr.has_next()){
            const Node &fld = itr.next();
            std:string fld_name = itr.name();
            index_t ncomps = 1;

            if(fld.has_child("values")){
                if(fld["values"].dtype().is_float64()){
                    const Node &fld_val = fld["values"];
                    char var_name[50]="";
                    DataType v_dt=fld_val.dtype();
                    int num_ele=v_dt.number_of_elements();
		    std::cout << "n ele " << num_ele << std::endl;
                    int ele_size=v_dt.element_bytes();
                    std::string var = itr.name();
                    sprintf(var_name,"field_%s", var.c_str());
                    char l_str[100], g_str[100],o_str[100];
                    sprintf (g_str, "%d", num_ele);
                    sprintf (l_str, "%d", num_ele/par_size);
                    int offset=m_rank*(num_ele/par_size);
                    sprintf (o_str, "%d", offset);
                    std::cout<<g_str<<" vbn "<<l_str<<"  "<<o_str<<"  "<< m_rank<<"\n";
                    int64_t var_id = adios_define_var (m_adios_group, var_name,"", adios_double, l_str,g_str, o_str);
		    adios_define_var_mesh(m_adios_group, var_name,var_mesh.c_str());
                    if(fld.has_child("association")){
			std::string association = fld["association"].as_string();
                        if(association == "vertex"){
				std::string assoc = "point";
				adios_define_var_centering(m_adios_group, var_name, assoc.c_str());
			}
			else{
				std::string assoc = "cell";
				adios_define_var_centering(m_adios_group, var_name, assoc.c_str());
			}		
                    }
                    //adios_set_transform (var_id, "none");
                    adios_write(m_adios_file, var_name, (void *)fld_val.as_float64_ptr());
                }
		else{    
                    NodeConstIterator field_itr = fld["values"].children();
                    int i = 0;
                    while(field_itr.has_next()){
                        const Node &fld_val = field_itr.next();
                        char var_name[50]="";
                        DataType v_dt=fld_val.dtype();
                        int num_ele=v_dt.number_of_elements();
                        int ele_size=v_dt.element_bytes();
                        std::string var = field_itr.name();
                        sprintf(var_name,"%s%d", var.c_str(), i);
                        std::cout << "var name here: " << var_name << std::endl;
                        i++;
                        char l_str[100], g_str[100],o_str[100];
                        sprintf (g_str, "%d", num_ele);
                        sprintf (l_str, "%d", num_ele/par_size);

                        int offset=m_rank*(num_ele/par_size);
                        sprintf (o_str, "%d", offset);
                        std::cout<<g_str<<" vbn "<<l_str<<"  "<<o_str<<"  "<< m_rank<<"\n";
                        int64_t var_id = adios_define_var (m_adios_group, var_name,"", adios_double, l_str,g_str,o_str);
                        adios_set_transform (var_id, "none");
                       // char dim[] ={10,10,10};
                       // char axis[] = "XYZ";
                       // const char mesh[] = "rectilinearmesh";
                       // adios_define_mesh_rectilinear (dim, axis,"", m_adios_group , mesh);

                        adios_write_byid(m_adios_file, var_id, (void *)fld_val.as_float64_ptr());

                    }
                }
            }
        }
    }*/
    if (options.has_child("render")){
	const Node &renderer = options["render"];
	std::string render = renderer["type"].as_string();
	adios_define_attribute(m_adios_group, "render", "", adios_string, render.c_str(),"");
	if (render == "isovalue"){
		const Node &iso  = renderer["values"];
		DataType iso_val = iso.dtype();
                int num_ele      = iso_val.number_of_elements();
		adios_define_attribute_byvalue(m_adios_group, "isovalues", "", adios_double, num_ele, (void *) iso.as_float64_ptr());
		if(renderer.has_child("num_values")){
			const Node &iso_num = renderer["num_values"];
			adios_define_attribute_byvalue(m_adios_group, "isovalues_number", "", adios_integer,1, (void *) iso_num.as_int_ptr());
 		}
	}   
        if (render == "isosurface"){
                const Node &iso  = renderer["values"];
                DataType iso_val = iso.dtype();
                int num_ele      = iso_val.number_of_elements();
                adios_define_attribute_byvalue(m_adios_group, "isosurface values", "", adios_double, num_ele, (void *) iso.as_float64_ptr());
                if(renderer.has_child("num_values")){
                        const Node &iso_num = renderer["num_values"];
                        adios_define_attribute_byvalue(m_adios_group, "isovalues_number", "", adios_integer,1, (void *) iso_num.as_int_ptr());
                }
        }  	
    }
//                adios_define_mesh_rectilinear("11,11,11", "coords_x,coords_y,coords_z", 0, m_adios_group, "rectilinearmesh");

     adios_close (m_adios_file);

     MPI_Barrier (m_mpi_comm);

     adios_finalize (m_rank);
	
     #endif
}



//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//
// Creation and Destruction
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
AdiosPipeline::AdiosPipeline()
:Pipeline(), 
 m_io(NULL)
{

}

//-----------------------------------------------------------------------------
AdiosPipeline::~AdiosPipeline()
{
    Cleanup();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//
// Main pipeline interface methods, which are used by the alpine interface.
//
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------

//-----------------------------------------------------------------------------
void
AdiosPipeline::Initialize(const conduit::Node &options)
{
#if PARALLEL
    if(!options.has_child("mpi_comm"))
    {
        ALPINE_ERROR("Missing Alpine::Open options missing MPI communicator (mpi_comm)");
    }

    int mpi_handle = options["mpi_comm"].value();
    MPI_Comm mpi_comm = MPI_Comm_f2c(mpi_handle);
    
    m_io = new IOManager(mpi_comm);
#else
    m_io = new IOManager();
#endif

}


//-----------------------------------------------------------------------------
void
AdiosPipeline::Cleanup()
{
    if(m_io != NULL)
    {
        delete m_io;
    }

    m_io = NULL;
}

//-----------------------------------------------------------------------------
void
AdiosPipeline::Publish(const conduit::Node &data)
{
    m_data.set_external(data);
}

//-----------------------------------------------------------------------------
void
AdiosPipeline::Execute(const conduit::Node &actions)
{
    //
    // Loop over the actions
    //
    for (int i = 0; i < actions.number_of_children(); ++i)
    {
        const Node &action = actions.child(i);
        ALPINE_INFO("Executing " << action["action"].as_string());
        if (action["action"].as_string() == "save")
        {
            m_io->SaveToAdiosFormat(m_data,action);
        }
        else
        {
            ALPINE_INFO("Warning : unknown action "
                          << action["action"].as_string());
        }
    }
}






//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
// -- end alpine:: --
//-----------------------------------------------------------------------------



