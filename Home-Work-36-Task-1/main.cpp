#include <QApplication>
#include <QWidget>
#include <QSlider>
#include <QVBoxLayout>
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>

enum COLOR {
    GREEN,
    YELLOW,
    RED
};

class MainWindow : public QWidget {
public:
    MainWindow() { move(800, 400);}
};

class Circle : public QWidget {
public:
    Circle() {
        setFixedSize(200, 200);
        currentMap = QPixmap("green.png");
        update();
    }

    void rePaint(int color) {
        currentMap = (color == GREEN) ? QPixmap("green.png") :
                     (color == YELLOW) ? QPixmap("yellow.png") : QPixmap("red.png");
        update();
    }

    void paintEvent(QPaintEvent* e) override {
        QPainter painter(this);
        painter.drawPixmap(e->rect(), currentMap);
    }

private:
    QPixmap currentMap;
};

class Slider : public QSlider {
public:
    Slider() {
        setMinimum(0);
        setMaximum(100);
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto* mainWindow = new MainWindow;

    auto* circle = new Circle;

    auto* slider = new QSlider(Qt::Horizontal);
    
    auto* layout = new QVBoxLayout(mainWindow);
    layout->addWidget(circle);
    layout->addWidget(slider);

    QObject::connect(slider, &QSlider::valueChanged, [&](int newValue) {
        (newValue < 34) ? circle->rePaint(GREEN) :
        (newValue > 33 && newValue < 67) ? circle->rePaint(YELLOW) : circle->rePaint(RED);
        });
 
    mainWindow->show();

    return a.exec();
}
