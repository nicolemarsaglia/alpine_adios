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
#include <vector> 
#include <algorithm>
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
    cout << "# of ranks " << par_size << endl;

    //Spacing, dims, orig are local
    char* sp;
    string space;
    char dims[3] = "";
    char* orig;
    char cell_orig[3] = "";
    char cell_local_dims[3] = "";

    //global dim & g_dim and global origin & g_origin are global
    char global_dim[3] = "";
    char global_origin[3] = "";
    char cell_global_dim[3] = "";
    char cell_global_orig[3] = "";
    int g_dim[3];
    double g_origin[3]; 
    double cell_g_origin[3];
    int cell_g_dim[3];

    //space mesh, local origin, and local dim are local, correspond to the local char arrays above. 
    double space_mesh[3];
    double local_origin[3];
    int local_dim[3];
    int cell_l_dim[3]; 
    int cell_origin[3];

    //max dim is used to find the global dimensions
    int max_dim[3]; //local dim + local origin then mpi reduction to find max among ranks


    NodeConstIterator itr = data["coordsets"].children();
    while(itr.has_next()){
         const Node &coordset = itr.next();
         std::string coordset_name = itr.name();
         std::string coordset_type = coordset["type"].as_string();
         if(coordset_type == "uniform"){
                if(coordset.has_child("spacing")){
			const Node &spacing = coordset["spacing"];
			if(spacing.has_child("dx")){
				space_mesh[0] = spacing["dx"].to_float64();
			}
                        if(spacing.has_child("dy")){
                                space_mesh[1] = spacing["dy"].to_float64();
                        }
                        if(spacing.has_child("dz")){
                                space_mesh[2] = spacing["dz"].to_float64();
                        }
			stringstream ss;
			ss << space_mesh[0] << "," << space_mesh[1] << "," << space_mesh[2];
                	space = ss.str();
                        cout << "rank: " << m_rank << " SPACING: " << space<<endl;
			sp = new char[space.length() + 1];
			strcpy(sp, space.c_str());
		}
                if(coordset.has_child("origin")){
        		const Node &origin = coordset["origin"];
			if(origin.has_child("x")){
				double o = origin["x"].as_float64();
				local_origin[0] = o/space_mesh[0];
			}                
			if(origin.has_child("y")){             
                                double o = origin["y"].as_float64();
                                local_origin[1] = o/space_mesh[1];
                        }
			if(origin.has_child("z")){             
                                double o = origin["z"].as_float64();
                                local_origin[2] = o/space_mesh[2];
                        }  	
			
			MPI_Reduce(local_origin,g_origin,3, MPI_DOUBLE,MPI_MIN,0,MPI_COMM_WORLD);
			if(m_rank == 0){ 
                        	sprintf(global_origin, "%f,%f,%f", g_origin[0], g_origin[1], g_origin[2]);
			}
			stringstream ss;
			ss << local_origin[0] << "," << local_origin[1] << "," << local_origin[2];
			string o = ss.str();
			orig = new char[o.length() + 1];
			strcpy(orig, o.c_str());
			//sprintf(orig, "%d,%d,%d", (int)local_origin[0],(int)local_origin[1],(int)local_origin[2]);
              		cout << "ORIGIN: " << orig << endl;
		}
              if(coordset.has_child("dims")){
                        const Node &dimensions = coordset["dims"];
			if(dimensions.has_child("i")){
				int d = dimensions["i"].as_int32();
				max_dim[0] = d + (int)local_origin[0];
				local_dim[0] = d;
			}
                        if(dimensions.has_child("j")){
                                int d = dimensions["j"].as_int32();
                                max_dim[1] = d + (int)local_origin[1];
                                local_dim[1] = d;
                        }
                        if(dimensions.has_child("k")){
                                int d = dimensions["k"].as_int32();
                                max_dim[2] = d + (int)local_origin[2];
                                local_dim[2] = d;
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
			cout << "mesh spacing: " << sp << endl;
                	adios_define_mesh_uniform(global_dim, global_origin, sp, 0, "3", m_adios_group, "uniformmesh");
                	adios_define_mesh_timevarying ("no", m_adios_group, type.c_str());
		}
        //	adios_define_attribute(m_adios_group, "mesh", "", adios_string, "uniformmesh","");
        }
        else if(coordset_type == "rectilinear"){
		int sum_dim[3];
		const double * x;
		const double * y;
		const double * z;
		if(coordset.has_child("values")){
			const Node &coord_values = coordset["values"];
			if(coord_values.has_child("x")){
				cout << "HAS X CHILD" << endl;
				const Node &x_coords = coord_values["x"];
			        DataType x_dt=x_coords.dtype();
                        	int num_ele=x_dt.number_of_elements();
                        	int ele_size=x_dt.element_bytes();
				cout << "number of x coords " << num_ele<<endl;
				local_dim[0] = num_ele;
				cell_l_dim[0] = num_ele - 1;
				coord_values.print();
				x = x_coords.as_float64_ptr();
				
			}
			if(coord_values.has_child("y")){
				cout << "HAS Y CHILD" << endl;
				const Node &y_coords = coord_values["y"];
			        DataType y_dt=y_coords.dtype();
                        	int num_ele=y_dt.number_of_elements();
                        	int ele_size=y_dt.element_bytes();
				cout << "number of y coords " << num_ele<<endl;
				local_dim[1] = num_ele;
				cell_l_dim[1] = num_ele - 1;
				coord_values.print();
				y = y_coords.as_float64_ptr();
			}
			if(coord_values.has_child("z")){
				cout << "HAS Z CHILD" << endl;
				const Node &z_coords = coord_values["z"];
			        DataType z_dt=z_coords.dtype();
                        	int num_ele=z_dt.number_of_elements();
                        	int ele_size=z_dt.element_bytes();
				cout << "number  of z coords " << num_ele<<endl;
				local_dim[2] = num_ele;
				cell_l_dim[2] = num_ele - 1;
				coord_values.print();
				//need local length of coords and global length.
				z = z_coords.as_float64_ptr();
			}
		}
		int max_dim[3];
		char m_dim[3];
		MPI_Allreduce(local_dim,max_dim,3, MPI_INT,MPI_MAX,MPI_COMM_WORLD);
		int x_max = max_dim[0], y_max = max_dim[1], z_max = max_dim[2];
		int x_allocate = x_max * par_size;
		int y_allocate = y_max * par_size;
		int z_allocate = z_max * par_size;
		cout << "x allocate : " << x_allocate << endl;

		double *x_local = new double[x_allocate];
		double *y_local = new double[y_allocate];
		double *z_local = new double[z_allocate];
		double *x_array = new double[x_allocate];
		double *y_array = new double[y_allocate];
		double *z_array = new double[z_allocate];

		for (int i = 0; i < x_allocate; i++)
			x_local[i] = 0.0;
		for (int i = 0; i < y_allocate; i++)
			y_local[i] = 0.0;
		for (int i = 0; i < z_allocate; i++)
			z_local[i] = 0.0;

                int x_offset = m_rank*max_dim[0];
		int y_offset = m_rank*max_dim[1];
		int z_offset = m_rank*max_dim[2];

		
		for(int i = 0; i < max_dim[0]; i++){
			if (i < local_dim[0])
				x_local[i+x_offset] = x[i];
			else
				x_local[i+x_offset] = x_local[0];
		}			
		for(int i = 0; i < max_dim[1]; i++){
			if (i < local_dim[1])
				y_local[i+y_offset] = y[i];
			else
				y_local[i+y_offset] = y_local[0];
		}			
		for(int i = 0; i < max_dim[2]; i++){
			if (i < local_dim[2])
				z_local[i+z_offset] = z[i];
			else
				z_local[i+z_offset] = z_local[0];
		}		
			
		MPI_Allreduce(x_local,x_array,x_allocate, MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);
		MPI_Allreduce(y_local,y_array,y_allocate, MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);
		MPI_Allreduce(z_local,z_array,z_allocate, MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD);
	
		vector<double> x_vec(x_array, x_array + x_allocate);
		vector<double> y_vec(y_array, y_array + y_allocate);
		vector<double> z_vec(z_array, z_array + z_allocate);
	
		sort(x_vec.begin(), x_vec.end());
		sort(y_vec.begin(), y_vec.end());
		sort(z_vec.begin(), z_vec.end());
		
		vector<double> x_final;	
		vector<double> y_final;	
		vector<double> z_final;	
	
		for(int i = 0; i < x_vec.size(); i++){
			if(i == 0)
				x_final.push_back(x_vec[i]);
			else{
				if(x_vec[i-1] != x_vec[i])
					x_final.push_back(x_vec[i]);
			}
		}
		for(int i = 0; i < y_vec.size(); i++){
			if(i == 0)
				y_final.push_back(y_vec[i]);
			else{
				if(y_vec[i-1] != y_vec[i])
					y_final.push_back(y_vec[i]);
			}
		}
		for(int i = 0; i < z_vec.size(); i++){
			if(i == 0)
				z_final.push_back(z_vec[i]);
			else{
				if(z_vec[i-1] != z_vec[i])
					z_final.push_back(z_vec[i]);
			}
		}

		g_dim[0] = x_final.size();
		g_dim[1] = y_final.size();
		g_dim[2] = z_final.size();
		sprintf(global_dim, "%d,%d,%d", g_dim[0], g_dim[1], g_dim[2]);
		cell_g_dim[0] = x_final.size() - 1;
		cell_g_dim[1] = y_final.size() - 1;
		cell_g_dim[2] = z_final.size() - 1;
		sprintf(cell_global_dim, "%d,%d,%d", cell_g_dim[0], cell_g_dim[1], cell_g_dim[2]);
		
		double x_array_final[x_final.size()];	
		double y_array_final[y_final.size()];	
		double z_array_final[z_final.size()];

		copy(x_final.begin(), x_final.end(), x_array_final);	
		copy(y_final.begin(), y_final.end(), y_array_final);	
		copy(z_final.begin(), z_final.end(), z_array_final);

		for(int i = 0; i < x_final.size(); i++){
			if(x_array_final[i] == x[0]){
				local_origin[0] = i;
			} 
		}
		for(int i = 0; i < y_final.size(); i++){
			if(y_array_final[i] == y[0]){
				local_origin[1] = i;
			} 
		}
		for(int i = 0; i < z_final.size(); i++){
			if(z_array_final[i] == z[0]){
				local_origin[2] = i;
			} 
		}
		stringstream ss;
                ss << local_origin[0] << "," << local_origin[1] << "," << local_origin[2];
                string o = ss.str();
                orig = new char[o.length() + 1];
	        strcpy(orig, o.c_str());
			
	/*
 * 		TODO: remove duplicates of the x_array, z_array, y_array
 * 		find length of these results for global dimensions
 * 		use first from x_local, y_local, z_local to find offsets
 * 		finish defining rectilinear mesh with adios calls
 * 		Test
 * 		*/

               //TODO: Global dimensions 
              if(coordset.has_child("dims")){
			const Node &dimensions = coordset["dims"];
                        if(dimensions.has_child("i")){
                                int d = dimensions["i"].as_int32();
                                local_dim[0] = d;
                        }
                        if(dimensions.has_child("j")){
                                int d = dimensions["j"].as_int32();
                                local_dim[1] = d;
                        }
                        if(dimensions.has_child("k")){
                                int d = dimensions["k"].as_int32();
                                local_dim[2] = d;
                        }
                        sprintf(dims, "%d,%d,%d", local_dim[0],local_dim[1],local_dim[2]);
		}
                else{   
                        sprintf(dims, "%d,%d,%d", local_dim[0],local_dim[1],local_dim[2]);
                        sprintf(cell_local_dims, "%d,%d,%d", cell_l_dim[0],cell_l_dim[1],cell_l_dim[2]);
                	cout <<"rank: " << m_rank <<  " Dimensions Not Provided, Using Local Dims: " << dims << endl;
		}
		char x_size[1], y_size[1], z_size[1];
		sprintf(x_size, "%d", x_final.size());
		sprintf(y_size, "%d", y_final.size());
		sprintf(z_size, "%d", z_final.size());
                std::string type = "rectilinearmesh";
                var_mesh = type;
                adios_define_mesh_timevarying ("no", m_adios_group, type.c_str());
                if(m_rank == 0){
                      	int64_t x_id = adios_define_var (m_adios_group, "coords_x","", adios_double, x_size,x_size,"");
                        adios_set_transform (x_id, "none");
                        adios_write_byid(m_adios_file, x_id, (void *)x_array_final);
                      	
			int64_t y_id = adios_define_var (m_adios_group, "coords_y","", adios_double, y_size,y_size,"");
                        adios_set_transform (y_id, "none");
                        adios_write_byid(m_adios_file, y_id, (void *)y_array_final);
                    	
			int64_t z_id = adios_define_var (m_adios_group, "coords_z","", adios_double, z_size,z_size,"");
                       	adios_set_transform (z_id, "none");
                       	adios_write_byid(m_adios_file, z_id, (void *)z_array_final);
			
			adios_define_mesh_rectilinear(global_dim, "coords_x,coords_y,coords_z", 0, m_adios_group, type.c_str());
        	}
	}
         else   
                std::cout << "coordset type " << coordset_type <<std::endl;
    }
    //TODO: need dims to reflect cell or vertex centering of field
    if(data.has_child("fields")){
        cout << "rank " << m_rank << " in fields" << endl;
        string field_name = options["field_name"].as_string();
        const Node &fld = data["fields"][field_name];
        if (fld.has_child("values")){
                    const Node &fld_val = fld["values"];
                    char var_name[50]="";
                    DataType v_dt=fld_val.dtype();
                    int num_ele=v_dt.number_of_elements();
                    int ele_size=v_dt.element_bytes();
                    if(fld.has_child("association")){
                        std::string association = fld["association"].as_string();
                        if(association == "vertex"){
                    		int64_t var_id = adios_define_var (m_adios_group, field_name.c_str(),"", adios_double, dims ,global_dim, orig);
		    		cout << "rank: " << m_rank << " ldim: " << dims << " gdim: " << global_dim << " lorigin: " << orig<<endl;
		    		adios_define_attribute(m_adios_group, "field_name", "", adios_string, field_name.c_str(),"");
                    		adios_define_var_mesh(m_adios_group, field_name.c_str(),var_mesh.c_str());
                                std::string assoc = "point";
                                adios_define_var_centering(m_adios_group, field_name.c_str(), assoc.c_str());
                        }
                        else{
                    		int64_t var_id = adios_define_var (m_adios_group, field_name.c_str(),"", adios_double, cell_local_dims ,cell_global_dim, orig);
		    		cout << "rank: " << m_rank << " ldim: " << cell_local_dims << " gdim: " << cell_global_dim << " lorigin: " << orig<<endl;
		    		adios_define_attribute(m_adios_group, "field_name", "", adios_string, field_name.c_str(),"");
                    		adios_define_var_mesh(m_adios_group, field_name.c_str(),var_mesh.c_str());
                                std::string assoc = "cell";
                                adios_define_var_centering(m_adios_group, field_name.c_str(), assoc.c_str());
                        }               
                    }
                    //adios_set_transform (var_id, "none");
                    double * buff = new double[num_ele];
		    for (int i = 0; i < num_ele; i ++)
			buff[i] = i;
			
			adios_write(m_adios_file, field_name.c_str(), (void *)fld_val.as_float64_ptr());
			//adios_writ(m_adios_file, field_name.c_str(), (void *)buff);
	}

    }
//=======CLEANUP =======

//delete sp;


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



