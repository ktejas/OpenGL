/*
        Copyright 2015 Etay Meiri

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SSAO_TECHNIQUE_H
#define	SSAO_TECHNIQUE_H

#include "technique.h"
#include "ogldev_math_3d.h"
#include "ogldev_io_buffer.h"


class SSAOTechnique : public Technique {
public:

    SSAOTechnique();

    virtual bool Init();

    void BindDepthBuffer(IOBuffer& depthBuf);	
    void SetSampleRadius(float sr);    
    void SetProjMatrix(const Matrix4f& m);
    void SetAspectRatio(float aspectRatio);
    void SetTanHalfFOV(float tanHalfFOV);
    
private:
    
    void GenKernel();
    
    const static uint KERNEL_SIZE = 64;

    GLuint m_depthTextureUnitLocation;
    GLuint m_sampleRadLocation;    
    GLuint m_kernelLocation;
    GLuint m_projMatrixLocation;
    GLuint m_aspectRatioLocation;
    GLuint m_tanHalfFOVLocation;
};


#endif	/* SSAO_TECHNIQUE_H */
