#include "multiclickbutton.h"

MultiClickButton::MultiClickButton(QWidget* parent, int i): QPushButton(parent)
{
    id = i;
}
void MultiClickButton::mouseReleaseEvent(QMouseEvent* e){
    setDown(false);
    if (e->button() == Qt::RightButton)
        emit rightClicked();
    else if (e->button() == Qt::LeftButton)
        emit clicked();
}

int MultiClickButton::getID(){
    return id;
}
