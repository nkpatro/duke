/*
 * GLUtils.h
 *
 *  Created on: Nov 28, 2012
 *      Author: Guillaume Chatelet
 */

#ifndef GLUTILS_H_
#define GLUTILS_H_

#include <string>

void checkError();
void checkShaderError(unsigned int shaderId, const char* source);
void checkProgramError(unsigned int programId);
std::string slurpFile(const char* pFilename);

#endif /* GLUTILS_H_ */
