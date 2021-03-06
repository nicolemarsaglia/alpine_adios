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
/// file: alpine_icet_compositor.hpp
///
//-----------------------------------------------------------------------------
#ifndef ALPINE_ICET_COMPOSITOR_HPP
#define ALPINE_ICET_COMPOSITOR_HPP

//----iceT includes 
#include <IceT.h>
#include <IceTMPI.h>
#include "alpine_compositor_base.hpp"
//-----------------------------------------------------------------------------
// -- begin alpine:: --
//-----------------------------------------------------------------------------
namespace alpine
{

class IceTCompositor : public Compositor
{
public:
     IceTCompositor();
    ~IceTCompositor();
    
    void              Init(MPI_Comm mpi_comm);
    
    // composite with given visibility ordering.
    
    unsigned char    *Composite(int                  width,
                                int                  height,
                                const unsigned char *color_buffer,
                                const int           *vis_order,
                                const float         *bg_color);
    unsigned char    *Composite(int                  width,
                                int                  height,
                                const float         *color_buffer,
                                const int           *vis_order,
                                const float         *bg_color);

    // composite with using a depth buffer.
    
    unsigned char    *Composite(int                  width,
                                int                  height,
                                const unsigned char *color_buffer,
                                const float         *depth_buffer,
                                const int           *viewport,
                                const float         *bg_color);

    unsigned char    *Composite(int                  width,
                                int                  height,
                                const float         *color_buffer,
                                const float         *depth_buffer,
                                const int           *viewport,
                                const float         *bg_color);


    void              Cleanup();
    
private:
    void                GetTimings(); 
    IceTCommunicator    m_icet_comm;
    IceTContext         m_icet_context;
    IceTImage           m_icet_image;
    int                 m_rank;
};

//-----------------------------------------------------------------------------
};
//-----------------------------------------------------------------------------
// -- end alpine:: --
//-----------------------------------------------------------------------------

#endif
//-----------------------------------------------------------------------------
// -- end header ifdef guard
//-----------------------------------------------------------------------------


