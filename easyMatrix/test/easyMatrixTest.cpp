/*************************************************************************
	> File Name: easyMatrix.c
	> Author: Zhang Yuteng
	> Mail:
	> Created Time: 2019年05月13日 星期一 22时15分52秒
 ************************************************************************/

#include <stdio.h>
extern "C" {
#include "easyMatrix.h"
}
#include "gtest/gtest.h"

declearMatrix(3,3);
declearMatrix(2,3);
declearMatrix(3,2);
declearMatrix(2,2);
declearMatrix(4,4);
declearMatrix(1,4);
declearMatrix(4,1);
declearMatrix(7,7);

float val[] = {1,2,3,4,5,6,7,8,9};
void expect(int i, int j,float* a, float* b) {
    int t = i*j;
    for(int ii=0;ii<t;++ii) {
        EXPECT_NEAR(a[ii],b[ii],1e-6);
    }
}

void expect(int i, int j,float* a, float val) {
    int t = i*j;
    for(int ii=0;ii<t;++ii) {
        EXPECT_NEAR(a[ii],val,1e-6);
    }
}
TEST(testCase, easyMatrixTest_SET) {
    easyMatrix3N3 M0;
    {
        setMatrix(3,3,val,M0.element);
        expect(3,3,val,M0.element);
    }
};

TEST(testCase, easyMatrixTest_ZEROS) {
    easyMatrix3N3 M0;
    setMatrix(3,3,val,M0.element);
    expect(3,3,val,M0.element);
    zerosMatrix(3,3,M0.element);
    expect(3,3,M0.element,0.0f);
};
TEST(testCase, easyMatrixTest_ONES) {
    easyMatrix3N3 M0;
    setMatrix(3,3,val,M0.element);
    expect(3,3,val,M0.element);
    float val1[] = {1,0,0,0,1,0,0,0,1};
    eyesMatrix(3,3,M0.element);
    expect(3,3,M0.element,val1);
};
TEST(testCase, easyMatrixTest_TRANS0) {
    easyMatrix3N3 M0,M1;
    setMatrix(3,3,val,M0.element);
    transMatrix(3,3,M0.element,M1.element);
    float val1[] = {1,4,7,2,5,8,3,6,9};
    expect(3,3,M1.element,val1);
}
TEST(testCase, easyMatrixTest_TRANS1) {
    easyMatrix2N3 N1;
    easyMatrix3N2 N2;
    setMatrix(2,3,val,N1.element);
    transMatrix(2,3,N1.element,N2.element);
    float val1[] = {1,4,2,5,3,6};
    expect(3,2,N2.element,val1);
}

TEST(testCase, easyMatrixTest_DET) {
    easyMatrix3N3 M0;
    setMatrix(3,3,val,M0.element);
    float result = detMatrix(3,3,M0.element);
    EXPECT_EQ(result,0);
}

TEST(testCase, easyMatrixTest_DET1) {
    easyMatrix3N3 M0;
    float val1[] = {1,3,4,5,6,7,2,3,5};
    setMatrix(3,3,val1,M0.element);
    float result = detMatrix(3,3,M0.element);
    EXPECT_EQ(result,-12);
}

TEST(testCase, easyMatrixTest_DET2) {
    easyMatrix2N2 M0;
    float val1[] = {1,3,4,5};
    setMatrix(2,2,val1,M0.element);
    float result = detMatrix(2,2,M0.element);
    EXPECT_EQ(result,-7);
}

TEST(testCase, easyMatrixTest_DET3) {
    easyMatrix4N4 M0;
    float val1[] = {1,2,3,4,
                    0,1,2,3,
                    0,0,1,2,
                    0,0,0,1};
    setMatrix(4,4,val1,M0.element);
    float result = detMatrix(4,4,M0.element);
    EXPECT_EQ(result,1);
}

TEST(testCase, easyMatrixTest_DET4) {
    easyMatrix3N3 M0;
    float val1[] = {1,2,3,
                    0,1,2,
                    0,0,1};
    setMatrix(3,3,val1,M0.element);
    float result = detMatrix(3,3,M0.element);
    EXPECT_EQ(result,1);
}

TEST(testCase, easyMatrixTest_DET5) {
    easyMatrix4N4 M0;
    float val1[] = {1,5,3,5,
                    5,6,8,1,
                    9,8,3,1,
                    4,3,2,7 };
    setMatrix(4,4,val1,M0.element);
    float result = detMatrix(4,4,M0.element);
    EXPECT_EQ(result,1475);
}

TEST(testCase, easyMatrixTest_DET7x7) {
    easyMatrix4N4 M0;
    float val1[] = {1,5,3,5,5,4,3,
                    5,6,8,1,1,6,9,
                    9,8,3,1,2,6,3,
                    4,3,2,7,3,4,5,
                    2,5,7,2,3,5,8,
                    1,2,5,3,7,9,3,
                    9,5,7,9,3,1,5
                    };
    setMatrix(7,7,val1,M0.element);
    float result = detMatrix(7,7,M0.element);
    EXPECT_EQ(result,-108006);
}

TEST(testCase, easyMatrixTest_ADD0) {
    easyMatrix4N4 M0;
    easyMatrix4N4 M1;
    easyMatrix4N4 M2;
    float val1[] = {1,3,4,5,3,2,5,6,1,2,3,4,1,2,3,4};
    float val2[] = {1,3,4,5,3,2,5,6,1,2,3,4,1,2,3,4};
    float val3[] = {1,3,4,5,3,2,5,6,1,2,3,4,1,2,3,4};
    for(int i=0;i<16;++i) val2[i] = val1[i] +1;
    for(int i=0;i<16;++i) val3[i] = 1;
    initMatrix4N4(val1,&M0);
    //setMatrix(4,4,val1,M0.element);
    initMatrix4N4(val3,&M1);
    //setMatrix(4,4,val3,M1.element);
    printf("m1:%d\n",M1.cols);
    addMatrix(&M1,&M0,&M2);

    expect(4,4,M2.element,val2);
}

TEST(testCase, easyMatrixTest_SUB0) {
    easyMatrix4N4 M0;
    easyMatrix4N4 M1;
    float val1[] = {1,3,4,5,3,2,5,6,1,2,3,4,1,2,3,4};
    float val2[] = {1,3,4,5,3,2,5,6,1,2,3,4,1,2,3,4};
    float val3[] = {1,3,4,5,3,2,5,6,1,2,3,4,1,2,3,4};
    for(int i=0;i<16;++i) val2[i] = val1[i] -1;
    for(int i=0;i<16;++i) val3[i] = 1;
    setMatrix(4,4,val1,M0.element);
    setMatrix(4,4,val3,M1.element);
    subMatrix(4,4,M0.element,M1.element,M1.element);

    expect(4,4,M1.element,val2);
}

TEST(testCase, easyMatrixTest_MUL0) {
    easyMatrix1N4 M0;
    easyMatrix4N1 M1;
    float val1[] = {1,2,3,4};
    setMatrix(1,4,val1,M0.element);
    setMatrix(4,1,val1,M1.element);
    float result;
    multiMatrix(1,4,M0.element,1,M1.element,&result);

    EXPECT_EQ(result,30);
}
TEST(testCase, easyMatrixTest_MUL1) {
    easyMatrix1N4 M0;
    easyMatrix4N1 M1;
    easyMatrix4N4 M2;
    float val1[] = {1,2,3,4};
    float val2[] = {1,2,3,4,2,4,6,8,3,6,9,12,4,8,12,16};
    setMatrix(1,4,val1,M0.element);
    setMatrix(4,1,val1,M1.element);
    multiMatrix(4,1,M1.element,4,M0.element,M2.element);
    expect(4,4,M2.element,val2);
}

TEST(testCase, easyMatrixTest_LEFT) {
    easyMatrix3N3 M0;
    easyMatrix2N2 M1;
    float val1[] = {1,2,3,4,2,4,6,8,3};
    float val2[] = {1,2,4,2};
    setMatrix(3,3,val1,M0.element);
    leftMatrix(3,3,2,2,M0.element,M1.element);

    expect(2,2,M1.element,val2);
}

TEST(testCase, easyMatrixTest_ADJ) {
    easyMatrix3N3 M0;
    easyMatrix3N3 M1;
    float val1[] = {1,2,3,1,0,-1,0,1,1};
    float val2[] = {1,1,-2,-1,1,4,1,-1,-2};
    setMatrix(3,3,val1,M0.element);
    adjMatrix(3,3,M0.element,M1.element);
    expect(3,3,M1.element,val2);
}
TEST(testCase, easyMatrixTest_INV) {
    easyMatrix3N3 M0;
    easyMatrix3N3 M1;
    easyMatrix3N3 M2;
    float val1[] = {1,2,3,1,0,-1,0,1,1};
    float val2[] = {0.5,0.5,-1.0,
                    -0.5,0.5,2.0,
                    0.5,-0.5,-1.0};
    setMatrix(3,3,val1,M0.element);
    invMatrix(3,3,M0.element,M1.element);
    expect(3,3,M1.element,val2);
    multiMatrix(3,3,val1,3,val2,M2.element);
    eyesMatrix(3,3,M0.element);
    expect(3,3,M0.element,M2.element);
}

TEST(testCase, easyMatrixTest_INV1) {
    easyMatrix7N7 M0;
    easyMatrix7N7 M1;
    easyMatrix7N7 M2;
    float val1[] = {1,5,3,5,5,4,3,
                    5,6,8,1,1,6,9,
                    9,8,3,1,2,6,3,
                    4,3,2,7,3,4,5,
                    2,5,7,2,3,5,8,
                    1,2,5,3,7,9,3,
                    9,5,7,9,3,1,5
                    };
    initMatrix7N7(val1,&M0);
    invMatrix(7,7,M0.element,M1.element);
    //invMatrix(&M0,&M1);
    multiMatrix(7,7,val1,7,M1.element,M2.element);
    eyesMatrix(7,7,M0.element);
    expect(7,7,M0.element,M2.element);
}
