/* This file can be generated using
 * javah -jni -classpath src/ -o jni/vectorAdd.h org.pocl.sample1.MainActivity
 */

/* DO NOT EDIT THIS FILE - it is machine generated */
#include <jni.h>
/* Header for class org_pocl_sample1_MainActivity */

#ifndef _Included_org_pocl_sample1_MainActivity
#define _Included_org_pocl_sample1_MainActivity
#ifdef __cplusplus
extern "C" {
#endif
/*
 * Class:     org_pocl_sample1_MainActivity
 * Method:    initCL
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_pocl_sample1_MainActivity_initCL
  (JNIEnv *, jobject);

/*
 * Class:     org_pocl_sample1_MainActivity
 * Method:    vectorAddCL
 * Signature: (I[F[F[F)I
 */
JNIEXPORT jint JNICALL Java_org_pocl_sample1_MainActivity_vectorAddCL
  (JNIEnv *, jobject, jint, jfloatArray, jfloatArray, jfloatArray);

/*
 * Class:     org_pocl_sample1_MainActivity
 * Method:    destroyCL
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_org_pocl_sample1_MainActivity_destroyCL
  (JNIEnv *, jobject);

/*
 * Class:     org_pocl_sample1_MainActivity
 * Method:    setenv
 * Signature: (Ljava/lang/String;Ljava/lang/String;)V
 */
JNIEXPORT void JNICALL Java_org_pocl_sample1_MainActivity_setenv
  (JNIEnv *, jobject, jstring, jstring);

#ifdef __cplusplus
}
#endif
#endif
