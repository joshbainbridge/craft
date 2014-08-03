#include <craft/segment.hpp>
#include <craft/simplex.hpp>

void dataConstructor ( float data[16][16][16], int xpos, int ypos, int zpos ) {

	for (int i = 0; i < 16; i += 1) {
		for (int j = 0; j < 16; j += 1) {
			for (int k = 0; k < 16; k += 1) {
				
				data[i][j][k] = simplex_noise(
					3,
					(float) i + (float) xpos * 16.0f,
					(float) j + (float) ypos * 16.0f,
					(float) k + (float) zpos * 16.0f,
					100.0f,
					0.85f
				) + ( ( (float) k + (float) zpos * 16.0f ) - 8.0f ) / 16;
				
			}
		}
	}
	
}

int bufferConstructor ( GLfloat *position,  float data[16][16][16], int xpos, int ypos, int zpos ) {
	int count = 0;
	int bi, bj, bk;
	char w, e, s, n, l, h;
	char check;
	
	for (int i = 0; i < 16; i += 1) {
		for (int j = 0; j < 16; j += 1) {
			for (int k = 0; k < 16; k += 1) {
				
				if (data[i][j][k] < 0) {
					
					check = 1;
					
					for (int ri = -1; ri < 2; ri += 1) {
						for (int rj = -1; rj < 2; rj += 1) {
							for (int rk = -1; rk < 2; rk += 1) {
								if ( ri != 0 || rj != 0 || rk != 0 ) {
									
									bi = i + ri;
									bj = j + rj;
									bk = k + rk;
									w = e = s = n = l = h = 0;
									
									if ( bi < 0 ) {
										// Check if West
										w = 1;
									}
									if ( bi > 15 ) {
										// Check if East
										e = 1;
									}
									if ( bj < 0 ) {
										// Check if South
										s = 1;
									}
									if ( bj > 15 ) {
										// Check if North
										n = 1;
									}
									if ( bk < 0 ) {
										// Check if Lower
										l = 1;
									} 
									if ( bk > 15 ) {
										// Check if Higher
										h = 1;
									}
									
									if ( w == 0 && e == 0 && s == 0 && n == 0 && l == 0 && h == 0 ) {
										
										// If neighbour is not beyond side, edge or corner
										if ( data[bi][bj][bk] > 0 ) {
											// Check if solid
											check = 0;
										}
										
									} else {
									
										if ( w == 1 ) {
									
											if ( s == 0 && n == 0 && l == 0 && h == 0 ) {
												// Check for West chunk
											} else {
										
												if ( s == 1 ) {
										
													if ( l == 1 ) {
														// Check for South West chunk and Lower segment
													} else if ( h == 1 ) {
														// Check for South West chunk and Higher segment
													} else {
														// Check for South West chunk
													}
										
												} else if ( n == 1 ) {
										
													if ( l == 1 ) {
														// Check for North West chunk and Lower segment
													} else if ( h == 1 ) {
														// Check for North West chunk and Higher segment
													} else {
														// Check for North West chunk
													}
										
												}
										
												if ( l == 1 ) {
											
													if ( s == 0 && n == 0 ) {
														// Check for West chunk and Lower segment
													}
										
												} else if ( h == 1 ) {
											
													if ( s == 0 && n == 0 ) {
														// Check for West chunk and Higher segment
													}
										
												}
										
											}
										
										} else if ( e == 1 ) {
									
											if ( s == 0 && n == 0 && l == 0 && h == 0 ) {
												// Check for East chunk
											} else {
										
												if ( s == 1 ) {
										
													if ( l == 1 ) {
														// Check for South East chunk and Lower segment
													} else if ( h == 1 ) {
														// Check for South East chunk and Higher segment
													} else {
														// Check for South East chunk
													}
										
												} else if ( n == 1 ) {
										
													if ( l == 1 ) {
														// Check for North East chunk and Lower segment
													} else if ( h == 1 ) {
														// Check for North East chunk and Higher segment
													} else {
														// Check for North East chunk
													}
										
												}
										
												if ( l == 1 ) {
											
													if ( s == 0 && n == 0 ) {
														// Check for East chunk and Lower segment
													}
										
												} else if ( h == 1 ) {
											
													if ( s == 0 && n == 0 ) {
														// Check for East chunk and Higher segment
													}
										
												}
										
											}
										
										}
									
										if ( s == 1 ) {
									
											if ( w == 0 && e == 0 && l == 0 && h == 0 ) {
												// Check for South chunk
											} else if ( l == 1 ) {
											
												if ( w == 0 && e == 0 ) {
													// Check for South chunk and Lower segment
												}
										
											} else if ( h == 1 ) {
											
												if ( w == 0 && e == 0 ) {
													// Check for South chunk and Higher segment
												}
										
											}
										
										} else if ( n == 1 ) {
									
											if ( w == 0 && e == 0 && l == 0 && h == 0 ) {
												// Check for North chunk
											} else if ( l == 1 ) {
											
												if ( w == 0 && e == 0 ) {
													// Check for North chunk and Lower segment
												}
										
											} else if ( h == 1 ) {
											
												if ( w == 0 && e == 0 ) {
													// Check for North chunk and Higher segment
												}
										
											}
										
										}
									
										if ( l == 1 ) {
									
											if ( w == 0 && e == 0 && s == 0 && n == 0 ) {
												// Check for Lower segment
											}
										
										} else if ( h == 1 ) {
									
											if ( w == 0 && e == 0 && s == 0 && n == 0 ) {
												// Check for Higher segment
											}
										
										}
									
									}
								}
							}
						}
					}
					
					
					if ( check == 0 ) {
						// If neighbour is empty
						position[count] = (float) i + (float) xpos * 16.0f;
						position[count + 1] = (float) j + (float) ypos * 16.0f;
						position[count + 2] = (float) k + (float) zpos * 16.0f;
						count += 3;
					}
					
				}
				
			}
		}
	}
	
	return count;
}

segment::segment () {
}

segment::segment (int xinput, int yinput, int zinput, GLuint attrib_input) {
	flag = 0;
	
	xpos = xinput;
	ypos = yinput;
	zpos = zinput;
	
	attrib_loc = attrib_input;
	
	dataConstructor( data, xpos, ypos, zpos );
	counter = bufferConstructor( buffer, data, xpos, ypos, zpos );
	
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);
	
}

void segment::render () {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(attrib_loc, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat)*3, 0);
	
	glDrawElementsInstanced( GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0, counter / 3 );
}

void segment::update (int xinput, int yinput, int zinput) {
	xpos = xinput;
	ypos = yinput;
	zpos = zinput;
	
	dataConstructor( data, xpos, ypos, zpos );
	counter = bufferConstructor( buffer, data, xpos, ypos, zpos );
	
	flag = 1;
}

void segment::updateBuffer () {
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(buffer), buffer, GL_STATIC_DRAW);
	
	flag = 0;
}

int segment::getypos () {
	return ypos;
}

char segment::getflag () {
	return flag;
}