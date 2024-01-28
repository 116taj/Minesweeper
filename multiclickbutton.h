#ifndef MULTICLICKBUTTON_H
#define MULTICLICKBUTTON_H
#include <QPushButton>
#include <QMouseEvent>
class MultiClickButton: public QPushButton
{
    Q_OBJECT
public:
    MultiClickButton(QWidget*,int=0);
    int getID();
protected:
    void mouseReleaseEvent(QMouseEvent*);
private:
    int id;
signals:
    void rightClicked();
};

#endif // MULTICLICKBUTTON_H
