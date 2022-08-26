#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ImageProcessing.h"
#include <opencv2/opencv.hpp>
#include <QString>
#include <QFileDialog>
#include <QMessageBox>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include <QScreen>
using namespace cv;

namespace Ui
{
    class ImageProcessing;
}

class ImageProcessing : public QMainWindow
{
    Q_OBJECT

public:
    ImageProcessing(QWidget *parent = nullptr);
    ~ImageProcessing();
    cv::Mat srcImage, dstImage, tempImage;
    QImage img;

private:
    Ui::ImageProcessingClass ui;

private slots:
    void on_actionOpen_triggered();//打开文件
    void on_actionRestore_triggered();//还原图像
    void on_actionSave_triggered();//保存图像
    void on_actionExit_triggered();//退出系统
    void on_actionClear_triggered();//清除标签内的图像
    void transfrom();//源图像处理图像转换

    void on_Horizen_triggered();//水平翻转
    void on_vertical_triggered();//垂直翻转
    void on_horizenAndVertical_triggered();//水平垂直

    void on_Erosion_triggered();//腐蚀
    void on_dilation_triggered();//膨胀
    /*void on_opening_triggered();//开运算
    void on_closing_triggered();//闭运算
    void on_Morphological_Gradient_triggered();//
    void on_topHat_triggered();//
    void on_blackHat_triggered();//
    void on_normalizeFilter_triggered();//
    void on_normalize_triggered();//
    void on_NoNormalize_triggered();//
    void on_GaussFilter_triggered();//
    void on_medianFilter_triggered();//
    void on_bilaterFilter_triggered();//
    void on_PyrUp_triggered();//
    void on_PyrDown_triggered();//
    void on_ResizeUp_triggered();//
    void on_ResizeDown_triggered();//
    void on_cNresize_triggered();//
    */

    void on_actionSobel_triggered();//Sobel
    void on_actionCanny_triggered();//Canny
    void on_actionLaplacian_triggered();//Laplacian
    void on_actionScharr_triggered();//Scharr
    //Sobel
    void on_actionDx_triggered();//dx
    void on_actionDy_triggered();//dy
    void on_actionDxDy_triggered();//dx&dy

    void on_actionsize1_triggered();//size=1
    void on_actionsize3_triggered();//size=3
    void on_actionsize5_triggered();//size=5
    void on_actionsize7_triggered();//size=7

    void on_actionscale05_triggered();//scale=0.5
    void on_actionscale1_triggered();//scale=1
    void on_actionscale2_triggered();//scale=2

    void on_actiondelta0_triggered();//delta=0
    void on_actiondelta50_triggered();//delta=50
    void on_actiondelta100_triggered();//delta=100


    void on_actionCopyright_triggered();//版权说明
    void on_actionAbout_triggered();//关于




};
