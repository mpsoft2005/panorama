
// Created by ben_xie on 2015-12-02.

#include <opencv2/opencv.hpp>

#include <iostream>
#include <string>
#include <cmath>
#include <cstdio>

using namespace cv;
using namespace std;

enum ARGV_INDEX {
    ARGV_EXE,
    ARGV_FOV,
    ARGV_CX,
    ARGV_CY,
    ARGV_R,
    ARGV_FISHEYE,
    ARGV_PANO,
};

static void initFisheyeToPanoMap(int fov, int center_x, int center_y, int _radius,
						  OutputArray map1, OutputArray map2)
{
    double radius = _radius * 180.0 / fov;
	double R = 2 * radius / M_PI;

	Size size((int)radius * 4, (int)radius * 2);
	map1.create( size, CV_32F );
	map2.create( size, CV_32F );

	for (int i = 0; i < size.height; i++) {
		float* m1f = map1.getMat().ptr<float>(i);
		float* m2f = map2.getMat().ptr<float>(i);
		for (int j = 0; j < size.width; j++) {
			double theta = (i - radius) / R;
			double phi = (radius * 3 - j) / R;

			double x = R * cos(theta) * cos(phi);
			double y = R * sin(theta);
			double z = R * cos(theta) * sin(phi);

			double theta2 = acos(z / R);
			double phi2 = atan2(y, x);

			double r = theta2 * R;

			double u = r * cos(phi2) + center_x;
			double v = r * sin(phi2) + center_y;

			m1f[j] = (float)u;
			m2f[j] = (float)v;
		}
	}
}


int main(int argc, char *argv[])
{
    if (argc < 6) {
        printf("usage:\n");
        printf("  %s <FOV> <center x> <center y> <radius> <fisheye image> <pano image>\n", argv[0]);
        exit(1);
    }

    int fov = atoi(argv[ARGV_FOV]);
    int center_x = atoi(argv[ARGV_CX]);
    int center_y = atoi(argv[ARGV_CY]);
    int radius = atoi(argv[ARGV_R]);

	Mat img = imread(argv[ARGV_FISHEYE]);

	if (img.empty()) {
        printf("read input image file failed!\n");
        exit(2);
	}

    Mat map1, map2, img_dc2;
    initFisheyeToPanoMap(fov, center_x, center_y, radius, map1, map2);
	remap(img, img_dc2, map1, map2, INTER_LINEAR, BORDER_CONSTANT);

	imshow("show image(dc2)", img_dc2);
	imwrite(argv[ARGV_PANO], img_dc2);

    waitKey();
	return 0;
}
