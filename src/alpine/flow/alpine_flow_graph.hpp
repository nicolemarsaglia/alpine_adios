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
/// file: alpine_flow_graph.hpp
///
//-----------------------------------------------------------------------------

#ifndef ALPINE_FLOW_GRAPH_HPP
#define ALPINE_FLOW_GRAPH_HPP

#include <alpine_flow_filter.hpp>


//-----------------------------------------------------------------------------
// -- begin alpine:: --
//-----------------------------------------------------------------------------
namespace alpine
{

//-----------------------------------------------------------------------------
// -- begin alpine::flow --
//-----------------------------------------------------------------------------
namespace flow
{

class Workspace;

//-----------------------------------------------------------------------------
///
/// Filter Graph
///
//-----------------------------------------------------------------------------

class Graph
{
public:
    
    friend class Workspace;
    friend class ExecutionPlan;
    
   ~Graph();

    /// access workspace that owns this graph
    Workspace &workspace();


    /// add a new filter of given type, and assigned name
    Filter *add_filter(const std::string &filter_type,
                       const std::string &name);


    /// add a new filter of given type, assigned name,
    /// and params
    Filter *add_filter(const std::string &filter_type,
                       const std::string &name,
                       const conduit::Node &params);

    /// add a new filter of given type, let the graph 
    /// generate a unique a name
    Filter *add_filter(const std::string &filter_type);

    /// add a new filter of given type using params
    /// let the graph generate a unique a name
    Filter *add_filter(const std::string &filter_type,
                       const conduit::Node &params);

    /// connect src filter to dest's input port
    /// using portname
    void connect(const std::string &src_name,
                 const std::string &des_name,
                 const std::string &port_name);

    /// connect src filter to dest's input port
    /// using port index
    void connect(const std::string &src_name,
                 const std::string &des_name,
                 int port_idx);


    /// check if this graph has a filter with passed name
    bool has_filter(const std::string &name);

    /// remove if filter with passed name from this graph
    void remove_filter(const std::string &name);

    /// this methods are used by save() and info()
    /// the produce conduit trees with data that can be used
    /// add_filters() and add_connections().

    /// Provides a conduit description of the filters in the graph
    void filters(conduit::Node &out) const;
    /// Provides a conduit description of the connections in the graph
    void connections(conduit::Node &out) const;

    /// adds a set of filters from a conduit tree that describes them
    void add_filters(const conduit::Node &filters);
    /// adds a set of connections from a conduit tree that describes them
    void add_connections(const conduit::Node &conns);


    /// adds a set of filters and connections from the given graph
    void add_graph(const Graph &g);
    /// adds a set of filters and connections from a conduit tree that 
    //  describes them
    void add_graph(const conduit::Node &g);


    /// remove all filters 
    void reset();

    /// save graph graph state to a conduit tree, 
    /// which can be used to restore the graph with load
    void save(conduit::Node &n);

    /// save graph graph state to a file, 
    /// which can be used to restore the graph with load
    void save(const std::string &ofile,
              const std::string &protocol="conduit_json");

    /// load graph from file
    ///  equiv to:
    ///   load n from ofile
    ///   reset();
    ///   add_filters(n["filters"]);
    ///   add_connections(n["connections"]);
    /// (Note: does not handle filter type registration)
    void load(const std::string &ofile,
              const std::string &protocol="conduit_json");
    
    /// load graph from conduit tree
    ///  equiv to:
    ///   reset();
    ///   add_filters(n["filters"]);
    ///   add_connections(n["connections"]);
    /// (Note: does not handle filter type registration)
    void load(const conduit::Node &n);

    /// create human understandable tree that describes the state
    /// of the workspace
    void           info(conduit::Node &out) const;
    /// create json string from info
    std::string    to_json() const;
    /// print json version of info
    void           print() const;

    /// create graphviz output
    std::string to_dot() const;

private:
    Graph(Workspace *w);

    const conduit::Node &edges()  const;
    const conduit::Node &edges_in(const std::string &f_name)  const;
    const conduit::Node &edges_out(const std::string &f_name) const;

    std::map<std::string,Filter*> &filters();


    Workspace                       *m_workspace;
    conduit::Node                    m_edges;
    std::map<std::string,Filter*>    m_filters;
    int                              m_filter_count;

};


//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
// -- end alpine::flow --
//-----------------------------------------------------------------------------



//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
// -- end alpine:: --
//-----------------------------------------------------------------------------

#endif
//-----------------------------------------------------------------------------
// -- end header ifdef guard
//-----------------------------------------------------------------------------


