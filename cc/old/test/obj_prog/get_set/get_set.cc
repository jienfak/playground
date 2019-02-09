#include <iostream>

using namespace std ;

class Canvas { public:
    void resize() {
        cout << "resize to " << width << " " << height << endl;
    }

    Canvas(int w, int h) : width(*this), height(*this) {
        cout << "new canvas " << w << " " << h << endl;
        width.value = w;
        height.value = h;
    }

    class Width { public:
        Canvas& canvas;
        int value;
        Width(Canvas& canvas): canvas(canvas) {}
        int & operator = (const int &i) {
            value = i;
            canvas.resize();
            return value;
        }
        operator int () const {
            return value;
        }
    } width;

    class Height { public:
        Canvas& canvas;
        int value;
        Height(Canvas& canvas): canvas(canvas) {}
        int & operator = (const int &i) {
            value = i;
            canvas.resize();
            return value;
        }
        operator int () const {
            return value;
        }
    } height;
};

int main() {
    Canvas canvas(256, 256);
    canvas.width = 128;
    canvas.height = 64;
}
