/**
 * @file helpers.h
 * @brief Helper function for standard types
 * @author Baudouin FEILDEL
 */
#ifndef __C_CONTAINERS_HELPER_H__
#define __C_CONTAINERS_HELPER_H__

#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Compare two integers
 * @param n1 First integer
 * @param n2 Second integer
 * @return   0 if n1 == n2. <br>
 * A value > 0 if n1 > n2.  <br>
 * A value < 0 if n1 < n2.  <br>
 */
inline int Int_cmp(int n1, int n2) { return n1 - n2; }

/**
 * Compare two float
 * @param n1 First float
 * @param n2 Second float
 * @return   0 if n1 == n2. <br>
 * A value > 0 if n1 > n2.  <br>
 * A value < 0 if n1 < n2.  <br>
 */
inline int Float_cmp(float n1, float n2) { return n1 - n2; }

/**
 * Compare two double
 * @param n1 First double
 * @param n2 Second double
 * @return   0 if n1 == n2. <br>
 * A value > 0 if n1 > n2.  <br>
 * A value < 0 if n1 < n2.  <br>
 */
inline int Double_cmp(double n1, double n2) { return n1 - n2; }

/**
 * Compare two strings
 * @details Use strcmp as a backend
 * @param str1 First string
 * @param str2 Second string
 * @return   0 if str1 == str2. <br>
 * A value > 0 if str1 > str2. <br>
 * A value < 0 if str1 < str2. <br>
 */
inline int Str_cmp(char * str1, char * str2) { return strcmp(str1, str2); }

/**
 * Copy integer value
 * @param dest Destination
 * @param src  Source
 */
inline void Int_copy(int * dest, int * src) { *dest = *src; }

/**
 * Copy float value
 * @param dest Destination
 * @param src  Source
 */
inline void Float_copy(float * dest, float * src) { *dest = *src; }

/**
 * Copy double value
 * @param dest Destination
 * @param src  Source
 */
inline void Double_copy(double * dest, double * src) { *dest = *src; }

/**
 * Copy a string
 * @param dest Destination
 * @param src  Source
 */
inline void Str_copy(char ** dest, char ** src)
{
	int i = 0, len = strlen(*src);
	*dest = calloc(sizeof(char) * len, sizeof(char));
	for(i = 0 ; i < len ; i++)
		(*dest)[i] = (*src)[i];
	(*dest)[len] = '\0';
}

inline void Int_free    (int      val) { (void)(val); }
inline void Float_free  (float    val) { (void)(val); }
inline void Double_free (double   val) { (void)(val); }
inline void Str_free    (char   * str) { free(str);   }

#ifdef __cplusplus
}
#endif
#endif // __C_CONTAINERS_HELPER_H__
