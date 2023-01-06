#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::string;


class Image {
protected:
	string path;
	int width;
	int height;
public:
	Image() = default;
	Image(string path, int width, int height) :
		path(path), width(width), height(height) {
		cout << "Image (" << path << ", " << width << ", " << height << ")" << endl;
	}
	virtual int getWidth() {
		return width;
	}
	virtual int getHeight() { // mora metoda da bude virtualna da bi mogla da se override u nasledjenoj klasi
		return height;
	}
	virtual void displayImage() {
		cout << "Displpay image from " << path << endl;
	}
	virtual void opisi() {
		cout << "Image : (" << path << ", " << width << ", " << height << ")" << endl;
	}
};

class ImageProxy : public Image {
private:
	Image* img = nullptr;
	string prxyPath;
	int prxyw;
	int prxyh;

	void createImage() {
		if (img) return;
		img = new Image(prxyPath, prxyw, prxyh);
	}
public:
	ImageProxy(string path, int width, int height) :
	prxyPath(path), prxyw(width), prxyh(height) {
	}
	int getWidth() override {
		createImage();
		return img->getWidth();
	}
	int getHeight() override {
		createImage();
		return img->getHeight();
	}
	void displayImage() override {
		createImage();
		img->displayImage();
	}

	~ImageProxy(){}
};

int main() {
	std::vector<Image*> album;
	Image* img1 = new ImageProxy("prva.png", 100, 200);
	Image* img2 = new ImageProxy("druga.png", 10, 200);
	Image* img3 = new ImageProxy("treca.png", 140, 240);
	img1->displayImage();
	album.push_back(img1);
	album.push_back(img2);
	album.push_back(img3);

	for (auto it = album.begin(); it != album.end(); it++) {
		(*it)->opisi();
	}

	return 0;
}