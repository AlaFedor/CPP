#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>
#include <cmath>

class Canvas {
protected:
    int width;
    int height;
    char background;
    std::vector<std::vector<char>> canvas;
    
public:
    Canvas(int w, int h, char b) : width(w), height(h), background(b) {
        canvas.resize(height+2, std::vector<char>(width+2, background));
        for (int j = 0; j < width+2; ++j) {
                canvas[0][j] = '=';
                canvas[height+1][j] = '=';
            }
        for (int i = 0; i < height + 2; ++i) {
            canvas[i][0] = '|';
            canvas[i][width + 1] = '|';
        }
    }
    virtual ~Canvas() {}
    void setPixel(int x, int y, char symbol) {
        if (x >= 0 && x < width && y >= 0 && y < height) {
            canvas[y+1][x+1] = symbol;
        }
    }
    int getWidth() const {
        return width;
    }
    int getHeight() const {
        return height;
    }
    void writeOut(std::string &filename) const {
        std::ofstream output(filename);
        for (int i = 0; i < height+2; ++i) {
            for (int j = 0; j < width+2; ++j) {
                output << canvas[i][j];
            }
            output << std::endl;
        }
        output.close();
    }
};

class ASCIICanvas : public Canvas {
public:
    ASCIICanvas(int signs, int lines, char b) : Canvas(signs, lines, b) {}
    ~ASCIICanvas(){}
};

class Figure {
protected:
    int x, y; //wspolrzedne srodka
    char symbol;

public:
    Figure(int x, int y, char symbol) : x(x), y(y), symbol(symbol) {}
    virtual ~Figure() {}
    virtual void draw(Canvas& canvas) const = 0;
};

class Rectangle : public Figure {
protected:
    int rwidth, rheight;

public:
    Rectangle(int x, int y, int rwidth, int rheight, char symbol) : Figure(x, y, symbol), rwidth(rwidth), rheight(rheight) {}
    ~Rectangle() {}
    void draw(Canvas& canvas) const override {
        int startX = x - rwidth / 2;
        int startY = y - rheight / 2;
        if(startX>=0 && startY>=0 && startX+rwidth<= canvas.getWidth() && startY+rheight<=canvas.getHeight()){
            for (int i = 0; i < rheight; ++i) {
                for (int j = 0; j < rwidth; ++j) {
                    canvas.setPixel(startX + j, startY + i, symbol);
                }
            }
        }
        else{
            std::cout<<"can't draw the rectangle or square"<<std::endl;
        }
    }
};

class Square : public Rectangle {
public:
    Square(int x, int y, int size, char symbol) : Rectangle(x, y, size, size, symbol) {}
    ~Square() {}
};

class Circle : public Figure {
private:
    int radius;

public:
    Circle(int x, int y, int radius, char symbol) : Figure(x, y, symbol), radius(radius) {}
    ~Circle() {}
    void draw(Canvas& canvas) const override {
        int canvasHeight = canvas.getHeight();
        int canvasWidth = canvas.getWidth();
        if(x-radius>=0 && y-radius>=0 && x+radius<=canvasWidth && y+radius<=canvasHeight){
            for (int i = 0; i < canvasHeight; ++i) {
                for (int j = 0; j < canvasWidth; ++j) {
                    if ((j - x) * (j - x) + (i - y) * (i - y) <= radius * radius) {
                        canvas.setPixel(j, i, symbol);
                    }
                }
            }
        }
        else{
            std::cout<<"can't draw the circle"<<std::endl;
        }
    }
};

void pars(std::string &filename, int &canvasWidth, int &canvasHeight, std::string &output, char &background, std::vector<std::unique_ptr<Figure>> &figures) {
    std::ifstream input(filename);
    if (!input.is_open()) {
        std::cout << "Can't open the config file!" << std::endl;
    }
    else{
        std::string key;
        while (input >> key) {
            if (key == "canvasWidth") {
               input >> canvasWidth;
            } else if (key == "canvasHeight") {
                input >> canvasHeight;
            } else if (key == "output") {
                input >> output;
            } else if (key == "background") {
                std::string line;
                std::getline(input, line);
                    background = line[1];
            } else if (key == "circle") {
                int x, y, radius;
                char symbol;
                input >> x >> y >> radius >> symbol;
                figures.push_back(std::make_unique<Circle>(x, y, radius, symbol));
            } else if (key == "rectangle") {
                int x, y, width, height;
                char symbol;
                input >> x >> y >> width >> height >> symbol;
                figures.push_back(std::make_unique<Rectangle>(x, y, width, height, symbol));
            } else if (key == "square") {
                int x, y, size;
                char symbol;
                input >> x >> y >> size >> symbol;
                figures.push_back(std::make_unique<Square>(x, y, size, symbol));
            }
        
        }
    }
}



int main (int argc, char* argv[]) {

    if(argc != 2){
        std::cout << "Enter the input file name" << std::endl;
        return -1;
    }
    std::string input = argv[1];
    int canvasWidth = 0;
    int canvasHeight = 0;
    std::string output;
    char background = ' ';
    std::vector<std::unique_ptr<Figure>> figures;
    pars(input, canvasWidth, canvasHeight, output, background, figures);

    if (canvasWidth <= 0 || canvasHeight <= 0) {
        std::cout << "Config file error!" << std::endl;
        return -1;
    }

    ASCIICanvas canvas(canvasWidth, canvasHeight, background);
    for (const auto& figure : figures) {
        figure->draw(canvas);
    }
    canvas.writeOut(output);

    return 0;
}