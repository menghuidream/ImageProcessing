#include "ImageProcessing.h"

ImageProcessing::ImageProcessing(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	
}

ImageProcessing::~ImageProcessing()
{}
//文件
void ImageProcessing::on_actionOpen_triggered()
{
	QString filename = QFileDialog::getOpenFileName(this, tr("Open"), "", tr("Image File(*.bmp *.jpg *.png"));
	std::string name = filename.toStdString();
	srcImage = cv::imread(name);
	if(!srcImage.data)
	{
		QMessageBox::information(this, "Error", tr("No Found!"));
	}
	else
	{
		//BGR转RGB
		cv::cvtColor(srcImage, srcImage, COLOR_BGR2RGB);
		img = QImage((const unsigned char*)(srcImage.data), srcImage.cols, srcImage.rows, srcImage.cols* srcImage.channels(), QImage::Format_RGB888);
		ui.label1->clear();
		img = img.scaled(ui.label1->width(), ui.label1->height());
		ui.label1->setPixmap(QPixmap::fromImage(img));
	}
}

void ImageProcessing::on_actionRestore_triggered()
{
	ui.label3->setPixmap(QPixmap::fromImage(img));
}

void ImageProcessing::on_actionSave_triggered()
{
	QString filename = QFileDialog::getSaveFileName(this, tr("Save"), "", tr("Image File(*.jpg *.bmp *.png"));
	//QScreen* screen = QGuiApplication::primaryScreen();
	//screen->grabWindow(ui.label2->winId()).save(filename);
	//img.save(filename);
	std::string name = filename.toStdString();
	cvtColor(srcImage, srcImage, COLOR_RGB2BGR);
	imwrite(name, srcImage);
}

void ImageProcessing::on_actionClear_triggered()
{
	ui.label1->clear();
	ui.label2->clear();
}

void ImageProcessing::on_actionExit_triggered()
{
    exit(0);//文件->退出
}

void ImageProcessing::transfrom()
{
	dstImage.copyTo(srcImage);
}
//翻转
void ImageProcessing::on_Horizen_triggered()
{
	flip(srcImage, dstImage, 1);
	img = QImage((const unsigned char*)(dstImage.data), dstImage.cols, dstImage.rows, dstImage.cols * dstImage.channels(), QImage::Format_RGB888);
	img = img.scaled(ui.label1->size());
	ui.label2->setPixmap(QPixmap::fromImage(img));
	transfrom();
}

void ImageProcessing::on_vertical_triggered()
{
	flip(srcImage, dstImage, 0);
	img = QImage((const unsigned char*)(dstImage.data), dstImage.cols, dstImage.rows, dstImage.cols * dstImage.channels(), QImage::Format_RGB888);
	img = img.scaled(ui.label1->size());
	ui.label2->setPixmap(QPixmap::fromImage(img));
	transfrom();
}

void ImageProcessing::on_horizenAndVertical_triggered()
{
	flip(srcImage, dstImage, -1);
	img = QImage((const unsigned char*)(dstImage.data), dstImage.cols, dstImage.rows, dstImage.cols * dstImage.channels(), QImage::Format_RGB888);
	img = img.scaled(ui.label1->size());
	ui.label2->setPixmap(QPixmap::fromImage(img));
	transfrom();
}
//形态
void ImageProcessing::on_Erosion_triggered()
{
	int erosion_type;
	erosion_type = MORPH_RECT;
	int erosion_size = 3;
	Mat element = getStructuringElement(erosion_type, Size(2 * erosion_size + 1, 2 * erosion_size + 1), Point(erosion_size, erosion_size));
	erode(srcImage, dstImage, element);
	img = QImage((const unsigned char*)(dstImage.data), dstImage.cols, dstImage.rows, dstImage.cols * dstImage.channels(), QImage::Format_RGB888);
	img = img.scaled(ui.label1->size());
	ui.label2->setPixmap(QPixmap::fromImage(img));
	transfrom();
}

void ImageProcessing::on_dilation_triggered()
{
	int dilation_type;
	dilation_type = MORPH_RECT;
	int dilation_size = 2;
	Mat element = getStructuringElement(dilation_type, Size(2 * dilation_size + 1, 2 * dilation_size + 1), Point(dilation_size, dilation_size));
	dilate(srcImage, dstImage, element);
	img = QImage((const unsigned char*)(dstImage.data), dstImage.cols, dstImage.rows, dstImage.cols * dstImage.channels(), QImage::Format_RGB888);
	img = img.scaled(ui.label1->size());
	ui.label2->setPixmap(QPixmap::fromImage(img));
	transfrom();
}
//边缘
void ImageProcessing::on_actionSobel_triggered()
{
	Sobel(srcImage, dstImage, srcImage.depth(), 0, 1);
	img = QImage((const unsigned char*)(dstImage.data), dstImage.cols, dstImage.rows, dstImage.cols * dstImage.channels(), QImage::Format_RGB888);
	img = img.scaled(ui.label1->size());
	ui.label2->setPixmap(QPixmap::fromImage(img));
	transfrom();
}

void ImageProcessing::on_actionCanny_triggered()
{
	Mat dstImage2;
	cv::resize(srcImage, srcImage, Size(ui.label1->width(), ui.label1->height()), 0, 0, 3);
	cvtColor(srcImage, dstImage2, COLOR_BGR2GRAY);
	Canny(dstImage2, dstImage2, 20, 100);
	img = QImage((const unsigned char*)(dstImage2.data), dstImage2.cols, dstImage2.rows, dstImage2.step, QImage::Format_Indexed8);
	ui.label2->setPixmap(QPixmap::fromImage(img));
}

void ImageProcessing::on_actionLaplacian_triggered()
{
	Laplacian(srcImage, dstImage, srcImage.depth());
	img = QImage((const unsigned char*)(dstImage.data), dstImage.cols, dstImage.rows, dstImage.cols * dstImage.channels(), QImage::Format_RGB888);
	img = img.scaled(ui.label1->size());
	ui.label2->setPixmap(QPixmap::fromImage(img));
	transfrom();
}

void ImageProcessing::on_actionScharr_triggered()
{
	Scharr(srcImage, dstImage, srcImage.depth(), 0, 1);
	img = QImage((const unsigned char*)(dstImage.data), dstImage.cols, dstImage.rows, dstImage.cols * dstImage.channels(), QImage::Format_RGB888);
	img = img.scaled(ui.label1->size());
	ui.label2->setPixmap(QPixmap::fromImage(img));
	transfrom();
}
//Soble
void ImageProcessing::on_actionDx_triggered()
{
	Sobel(srcImage, dstImage, srcImage.depth(), 1, 0);
	img = QImage((const unsigned char*)(dstImage.data), dstImage.cols, dstImage.rows, dstImage.cols * dstImage.channels(), QImage::Format_RGB888);
	img = img.scaled(ui.label1->size());
	ui.label2->setPixmap(QPixmap::fromImage(img));
	transfrom();
}

void ImageProcessing::on_actionDy_triggered()
{
	Sobel(srcImage, dstImage, srcImage.depth(), 0, 1);
	img = QImage((const unsigned char*)(dstImage.data), dstImage.cols, dstImage.rows, dstImage.cols * dstImage.channels(), QImage::Format_RGB888);
	img = img.scaled(ui.label1->size());
	ui.label2->setPixmap(QPixmap::fromImage(img));
	transfrom();
}

void ImageProcessing::on_actionDxDy_triggered()
{
	Sobel(srcImage, dstImage, srcImage.depth(), 1, 1);
	img = QImage((const unsigned char*)(dstImage.data), dstImage.cols, dstImage.rows, dstImage.cols * dstImage.channels(), QImage::Format_RGB888);
	img = img.scaled(ui.label1->size());
	ui.label2->setPixmap(QPixmap::fromImage(img));
	transfrom();
}
//size
void ImageProcessing::on_actionsize1_triggered()
{
	Sobel(srcImage, dstImage, srcImage.depth(), 1, 1,1);
	img = QImage((const unsigned char*)(dstImage.data), dstImage.cols, dstImage.rows, dstImage.cols * dstImage.channels(), QImage::Format_RGB888);
	img = img.scaled(ui.label1->size());
	ui.label2->setPixmap(QPixmap::fromImage(img));
	transfrom();
}

void ImageProcessing::on_actionsize3_triggered()
{
	Sobel(srcImage, dstImage, srcImage.depth(), 1, 1,3);
	img = QImage((const unsigned char*)(dstImage.data), dstImage.cols, dstImage.rows, dstImage.cols * dstImage.channels(), QImage::Format_RGB888);
	img = img.scaled(ui.label1->size());
	ui.label2->setPixmap(QPixmap::fromImage(img));
	transfrom();
}

void ImageProcessing::on_actionsize5_triggered()
{
	Sobel(srcImage, dstImage, srcImage.depth(), 1, 1,5);
	img = QImage((const unsigned char*)(dstImage.data), dstImage.cols, dstImage.rows, dstImage.cols * dstImage.channels(), QImage::Format_RGB888);
	img = img.scaled(ui.label1->size());
	ui.label2->setPixmap(QPixmap::fromImage(img));
	transfrom();
}

void ImageProcessing::on_actionsize7_triggered()
{
	Sobel(srcImage, dstImage, srcImage.depth(), 1, 1,7);
	img = QImage((const unsigned char*)(dstImage.data), dstImage.cols, dstImage.rows, dstImage.cols * dstImage.channels(), QImage::Format_RGB888);
	img = img.scaled(ui.label1->size());
	ui.label2->setPixmap(QPixmap::fromImage(img));
	transfrom();
}
//scale
void ImageProcessing::on_actionscale05_triggered()
{
	Sobel(srcImage, dstImage, srcImage.depth(), 1, 1, 7,0.5);
	img = QImage((const unsigned char*)(dstImage.data), dstImage.cols, dstImage.rows, dstImage.cols * dstImage.channels(), QImage::Format_RGB888);
	img = img.scaled(ui.label1->size());
	ui.label2->setPixmap(QPixmap::fromImage(img));
	transfrom();
}

void ImageProcessing::on_actionscale1_triggered()
{
	Sobel(srcImage, dstImage, srcImage.depth(), 1, 1, 7, 1);
	img = QImage((const unsigned char*)(dstImage.data), dstImage.cols, dstImage.rows, dstImage.cols * dstImage.channels(), QImage::Format_RGB888);
	img = img.scaled(ui.label1->size());
	ui.label2->setPixmap(QPixmap::fromImage(img));
	transfrom();
}

void ImageProcessing::on_actionscale2_triggered()
{
	Sobel(srcImage, dstImage, srcImage.depth(), 1, 1, 7, 2);
	img = QImage((const unsigned char*)(dstImage.data), dstImage.cols, dstImage.rows, dstImage.cols * dstImage.channels(), QImage::Format_RGB888);
	img = img.scaled(ui.label1->size());
	ui.label2->setPixmap(QPixmap::fromImage(img));
	transfrom();
}
//delta
void ImageProcessing::on_actiondelta0_triggered()
{
	Sobel(srcImage, dstImage, srcImage.depth(), 1, 1, 7, 1,0);
	img = QImage((const unsigned char*)(dstImage.data), dstImage.cols, dstImage.rows, dstImage.cols * dstImage.channels(), QImage::Format_RGB888);
	img = img.scaled(ui.label1->size());
	ui.label2->setPixmap(QPixmap::fromImage(img));
	transfrom();
}

void ImageProcessing::on_actiondelta50_triggered()
{
	Sobel(srcImage, dstImage, srcImage.depth(), 1, 1, 7, 1, 50);
	img = QImage((const unsigned char*)(dstImage.data), dstImage.cols, dstImage.rows, dstImage.cols * dstImage.channels(), QImage::Format_RGB888);
	img = img.scaled(ui.label1->size());
	ui.label2->setPixmap(QPixmap::fromImage(img));
	transfrom();
}

void ImageProcessing::on_actiondelta100_triggered()
{
	Sobel(srcImage, dstImage, srcImage.depth(), 1, 1, 7, 1, 100);
	img = QImage((const unsigned char*)(dstImage.data), dstImage.cols, dstImage.rows, dstImage.cols * dstImage.channels(), QImage::Format_RGB888);
	img = img.scaled(ui.label1->size());
	ui.label2->setPixmap(QPixmap::fromImage(img));
	transfrom();
}




void ImageProcessing::on_actionAbout_triggered()
{
	QMessageBox::information(this, "About", tr("The current version of this software is 1.0.0,"
		" which is developed by the author himself. All rights reserved. If you have any questions, please contact the author.   Tel:12345678"));
}

void ImageProcessing::on_actionCopyright_triggered()
{
	QMessageBox::information(this,"Copyright",tr("Developed by the author himself. All rights reserved."));
}
