#ifndef DARKNET_OBJECT_H
#define DARKNET_OBJECT_H

// #include <opencv2/imgproc/imgproc.hpp>

struct DetectedObject
{
    string object_class;
    float prob;
    int x;
    int y;
    int width;
    int height;
    // cv::Rect bounding_box;

    // DetectedObject() : object_class(-1), prob(0.){}
    // DetectedObject(int object_class, float prob, cv::Rect bb) : object_class(object_class), prob(prob), bounding_box(bb){}
};

#endif //DARKNET_OBJECT_H
