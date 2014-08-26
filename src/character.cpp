#include <craft/character.hpp>
#include <craft/shaderVoxel.hpp>
#include <craft/chunkController.hpp>

#define GLM_FORCE_RADIANS
#include <glm/gtc/constants.hpp>
#include <glm/gtc/matrix_inverse.hpp> 
#include <glm/gtc/matrix_transform.hpp>

#include <cmath>
#include <iostream>

void character::velocity () {
	if (xdown == 1) {
		xvel += 0.1f;
	} else if (xdown == -1) {
		xvel -= 0.1f;
	}

	if (ydown == 1) {
		yvel += 0.1f;
	} else if (ydown == -1) {
		yvel -= 0.1f;
	}

	if (zdown == 1) {
		zvel += 5.0f;
		zdown = 0;
	}
	
	zvel -= 0.5;

	if (xrdown == 1) {
		if (xrot < 1.0f) {
			xrvel += 0.01f;
			if (xrot + xrvel < xlimitmax) {
				xrot = xrot + xrvel;
			} else {
				xrot = xlimitmax;
				xlimitmax = xrot + 0.25f;
				xlimitmin = xrot - 0.25f;
				xrdown = 0;
			}
		}
	}
	
	if (xrdown == -1) {
		if (xrot > 0.0f) {
			xrvel -= 0.01f;
			if (xrot + xrvel > xlimitmin) {
				xrot = xrot + xrvel;
			} else {
				xrot = xlimitmin;
				xlimitmax = xrot + 0.25f;
				xlimitmin = xrot - 0.25f;
				xrdown = 0;
			}
		}
	}
	
	if (zrdown == 1) {
		zrvel += 0.01f;
		if (zrot + zrvel < zlimitmax) {
			zrot = zrot + zrvel;
		} else {
			zrot = zlimitmax;
			zlimitmax = zrot + 1.0f;
			zlimitmin = zrot - 1.0f;
			zrdown = 0;
		}
	}
	
	if (zrdown == -1) {
		zrvel -= 0.01f;
		if (zrot + zrvel > zlimitmin) {
			zrot = zrot + zrvel;
		} else {
			zrot = zlimitmin;
			zlimitmax = zrot + 1.0f;
			zlimitmin = zrot - 1.0f;
			zrdown = 0;
		}
	}
}

void character::collision (chunkController* chunkController01) {
	int xsegment = std::floor( xpos / 16 );
	int ysegment = std::floor( ypos / 16 );
	int zsegment = std::floor( zpos / 16 );
	
	if (zsegment < 7 && zsegment > 0) {
		std::vector< std::vector<chunk*> >* chunk_list = chunkController01->getChunkList();
		segment* segment = (*chunk_list)[4][4]->getSeg(zsegment);
	
		glm::vec3 abmaxVox;
		glm::vec3 abminVox;
	
		glm::vec3 abmax;
		glm::vec3 abmin;
	
		for (int xvox = 0; xvox < 16; xvox++) {
			for (int yvox = 0; yvox < 16; yvox++) {
				for (int zvox = 0; zvox < 16; zvox++) {
					if (segment->getData()[xvox][yvox][zvox] < 0) {
						abmaxVox = glm::vec3(xsegment * 16 + xvox + 1, ysegment * 16 + yvox + 1, zsegment * 16 + zvox + 1);
						abminVox = glm::vec3(xsegment * 16 + xvox, ysegment * 16 + yvox, zsegment * 16 + zvox);
						
						abmax = glm::vec3(xpos + xvel + size * 0.5, ypos + size * 0.5, zpos + size * 0.5);
						abmin = glm::vec3(xpos + xvel - size * 0.5, ypos - size * 0.5, zpos - size * 0.5);
						
						if (abmax[0] < abminVox[0] || abmaxVox[0] < abmin[0] || abmax[1] < abminVox[1] || abmaxVox[1] < abmin[1] || abmax[2] < abminVox[2] || abmaxVox[2] < abmin[2] ) {
						} else {
							xvel *= -1;
						}
						
						abmax = glm::vec3(xpos + size * 0.5, ypos + yvel + size * 0.5, zpos + size * 0.5);
						abmin = glm::vec3(xpos - size * 0.5, ypos + yvel - size * 0.5, zpos - size * 0.5);
						
						if (abmax[0] < abminVox[0] || abmaxVox[0] < abmin[0] || abmax[1] < abminVox[1] || abmaxVox[1] < abmin[1] || abmax[2] < abminVox[2] || abmaxVox[2] < abmin[2] ) {
						} else {
							yvel *= -1;
						}
						
						abmax = glm::vec3(xpos + size * 0.5, ypos + size * 0.5, zpos + zvel + size * 0.5);
						abmin = glm::vec3(xpos - size * 0.5, ypos - size * 0.5, zpos + zvel - size * 0.5);
						
						if (abmax[0] < abminVox[0] || abmaxVox[0] < abmin[0] || abmax[1] < abminVox[1] || abmaxVox[1] < abmin[1] || abmax[2] < abminVox[2] || abmaxVox[2] < abmin[2] ) {
						} else {
							zvel *= 0;
						}
					}
				}
			}
		}
	}
}

void character::transform () {
	buffer[0] = xpos - size * 0.5;
	buffer[1] = ypos - size * 0.5;
	buffer[2] = zpos - size * 0.5;
	
	view = glm::translate(glm::mat4(1.0f), glm::vec3(xpos, ypos, zpos));
	view = glm::rotate(view, glm::pi<float>() * -zrot, glm::vec3(0, 0, 1));
	view = view * glm::translate(glm::mat4(1.0f), glm::vec3(xvel, yvel, zvel));
	view = glm::rotate(view, glm::pi<float>() * xrot, glm::vec3(1, 0, 0));

	xpos = view[3][0];
	ypos = view[3][1];
	zpos = view[3][2];
	
	view = view * glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, nclip + 4));
	p = glm::vec3(view[3][0], view[3][1], view[3][2]);
	
	view = glm::affineInverse(view);
}

void character::frustumBuild () {
	d = glm::vec3(0.0f, 0.0f, -1.0f);
	
	cs = cos(glm::pi<float>() * xrot);
	sn = sin(glm::pi<float>() * xrot);

	yn = d[1] * cs - d[2] * sn;
	zn = d[1] * sn + d[2] * cs;

	d[1] = yn;
	d[2] = zn;

	cs = cos(glm::pi<float>() * -zrot);
	sn = sin(glm::pi<float>() * -zrot);

	xn = d[0] * cs - d[1] * sn;
	yn = d[0] * sn + d[1] * cs;
	
	d[0] = xn;
	d[1] = yn;
	
	right = glm::normalize( glm::cross(d, glm::vec3(0.0f,0.00001f,1.0f)) );
	up = glm::normalize(glm::cross(d, right));
	
	nearDist = nclip - 8.0f;
	Hnear = 8.0f * scale / ratio;
	Wnear = 8.0f * scale;
	
	farDist = fclip + 8.0f;
	Hfar = 8.0f * scale / ratio;
	Wfar = 8.0f * scale;
	
	view_frustum.fc = p + d * farDist;
	view_frustum.ftl = view_frustum.fc + (up * Hfar) - (right * Wfar);
	view_frustum.ftr = view_frustum.fc + (up * Hfar) + (right * Wfar);
	view_frustum.fbl = view_frustum.fc - (up * Hfar) - (right * Wfar);
	view_frustum.fbr = view_frustum.fc - (up * Hfar) + (right * Wfar);
	
	view_frustum.nc = p + d * nearDist;
	view_frustum.ntl = view_frustum.nc + (up * Hnear) - (right * Wnear);
	view_frustum.ntr = view_frustum.nc + (up * Hnear) + (right * Wnear);
	view_frustum.nbl = view_frustum.nc - (up * Hnear) - (right * Wnear);
	view_frustum.nbr = view_frustum.nc - (up * Hnear) + (right * Wnear);
	
	planes[0].init(view_frustum.ftr, view_frustum.fbl, view_frustum.ftl);
	planes[1].init(view_frustum.ntr, view_frustum.nbl, view_frustum.nbr);
	planes[2].init(view_frustum.fbl, view_frustum.ntl, view_frustum.ftl);
	planes[3].init(view_frustum.fbr, view_frustum.ntr, view_frustum.nbr);
	planes[4].init(view_frustum.nbl, view_frustum.fbr, view_frustum.nbr);
	planes[5].init(view_frustum.ntl, view_frustum.ftr, view_frustum.ftl);
	planes[6].init(glm::vec3(0, 1, 0), glm::vec3(1, 0, 0), glm::vec3(0, 0, 10));
}

void character::setFlagAuto () {
	if ( xvel == 0 && yvel == 0 && zvel == 0 && xrvel == 0 && zrvel == 0 ) {
		flag = 0;
	} else {
		flag = 1;
	}
}

character::character () {
}

character::character (float xpos_input, float ypos_input, float zpos_input, float ratio_input) {
	xpos = xpos_input;
	ypos = ypos_input;
	zpos = zpos_input;
	
	xseg = int( xpos / 16 );
	yseg = int( ypos / 16 );
	
	fov = 1.0f;
	ratio = ratio_input;
	nclip = 1.0f;
	fclip = 80.0f;
	scale = 9;
	
	size = 1;
	buffer[3] = size;
	
	xdown = 0;
	ydown = 0;
	zdown = 0;
	
	xvel = 0;
	yvel = 0;
	zvel = 0;
	
	xrot = 0.5f;
	zrot = 0.0f;
	
	zlimitmax = zrot + 1.0f;
	zlimitmin = zrot - 1.0f;
	xlimitmax = xrot + 0.25f;
	xlimitmin = xrot - 0.25f;
	
	xrdown = 0;
	zrdown = 0;
	
	xrvel = 0;
	zrvel = 0;
	
	init();
	
	flag = 0;
}

void character::init () {
	transform();
	
	proj = glm::ortho(
		-8.0f * scale,
		8.0f * scale,
		-8.0f * scale / ratio,
		8.0f * scale / ratio,
		nclip,
		fclip
	);
	
	frustumBuild();
}

void character::update (chunkController* chunkController01) {
	if (flag == 1) {
		velocity();
		
		collision(chunkController01);
		
		transform();
		
		frustumBuild();
		
		if (xvel != 0) {
			xvel *= 0.75;
			if ( (xvel < 0.01f && xvel > 0.0f) || (xvel > -0.01f && xvel < 0.0f) )
				xvel = 0; 
		}
		
		if (yvel != 0) {
			yvel *= 0.75;
			if ( (yvel < 0.01f && yvel > 0.0f) || (yvel > -0.01f && yvel < 0.0f) )
				yvel = 0; 
		}
		
		if (zvel != 0) {
			zvel *= 0.75;
			if ( (zvel < 0.01f && zvel > 0.0f) || (zvel > -0.01f && zvel < 0.0f) )
				zvel = 0; 
		}
		
		if (zrvel != 0) {
			zrvel *= 0.9;
			if ( (zrvel < 0.001f && zrvel > 0.0f) || (zrvel > -0.001f && zrvel < 0.0f) )
				zrvel = 0; 
		}
	
		if (xrvel != 0) {
			xrvel *= 0.5;
			if ( (xrvel < 0.001f && xrvel > 0.0f) || (xrvel > -0.001f && xrvel < 0.0f) )
				xrvel = 0; 
		}
	
		flag = 2;
	}
}

void character::updateUni(shaderVoxel* shader) {
	if (flag == 2) {
		glUniformMatrix4fv(shader->getUniView(), 1, GL_FALSE, glm::value_ptr( view ));
		glUniformMatrix4fv(shader->getUniProj(), 1, GL_FALSE, glm::value_ptr( proj ));
		
		setFlagAuto();
	}
	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(shader->getCoordAttrib(), 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*4, 0);
	glVertexAttribPointer(shader->getScaleAttrib(), 1, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*4, (const void*) (sizeof(float)*3));
	glDrawElementsInstanced( GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, 1 );
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

int character::frustumCheck (float x, float y, float z, float r) {
	glm::vec3 p(x, y, z);
	int inside = 1;
	
	for (int i = 0; i < 6; i++) {
		if (planes[i].intersection(p, r) != 1)
			inside = 0;
	}
	
	return inside;
}

void character::setXdown (int input) {
	xdown = input;
	flag = 1;
}

void character::setYdown (int input) {
	ydown = input;
	flag = 1;
}

void character::setZdown (int input) {
	zdown = input;
	flag = 1;
}

void character::setXseg (int input) {
	xseg = input;
}

void character::setYseg (int input) {
	yseg = input;
}

void character::setZrdown (int input) {
	zrdown = input;
	flag = 1;
}

void character::setXrdown (int input) {
	xrdown = input;
	flag = 1;
}

void character::setFov (float input) {
	fov = input;
}

void character::setNclip (float input) {
	nclip = input;
}

void character::setFclip (float input) {
	fclip = input;
}

void character::setFlag (int input) {
	flag = input;
}

glm::mat4 character::getView () {
	return view;
}

glm::mat4 character::getProj () {
	return proj;
}

float character::getXpos () {
	return xpos;
}

float character::getYpos () {
	return ypos;
}

float character::getZpos () {
	return zpos;
}

int character::getXseg () {
	return xseg;
}

int character::getYseg () {
	return yseg;
}

float character::getFov () {
	return fov;
}

float character::getNclip () {
	return nclip;
}

float character::getFclip () {
	return fclip;
}

int character::getFlag () {
	return flag;
}