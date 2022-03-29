#include <QApplication>
#include <QSlider>
#include <QVBoxLayout>
#include <QPixmap>
#include <QPainter>
#include <QPaintEvent>

class MainWindow : public QWidget {
public:
    MainWindow() {
        this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        this->resize(200, 200);
        this->move(800, 400);
    }

public slots:
    void reDraw(QPixmap& map) {
        currentMap = map;
        update();
    }

    void paintEvent(QPaintEvent* e) override {
        QPainter p(this);
        p.drawPixmap(e->rect(), currentMap);
    }

private:
    QPixmap currentMap;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    auto* mainWindow = new MainWindow;

    auto* slider = new QSlider(Qt::Horizontal, mainWindow);
    slider->setMinimum(0);
    slider->setMaximum(100);
    
    auto* layout = new QVBoxLayout(mainWindow);
    layout->addWidget(slider);

    QObject::connect(slider, &QSlider::valueChanged, [&](int newValue) {
        QPixmap map = (newValue > 0 && newValue < 34) ? QPixmap("green.png")
            : (newValue > 33 && newValue < 67) ? QPixmap("yellow.png") : QPixmap("red.png");
        slider->update();
        mainWindow->reDraw(map);
        });
 
    mainWindow->show();

    return a.exec();
}
