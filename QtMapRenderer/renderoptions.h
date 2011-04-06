#ifndef RENDEROPTIONS_H
#define RENDEROPTIONS_H

#include <QDialog>
#include <QFileDialog>
#include <QInputDialog>
#include "Map.h"

namespace Ui {
    class RenderOptions;
}

class RenderOptions : public QDialog
{
    Q_OBJECT

public:
    explicit RenderOptions(QWidget *parent = 0);
    ~RenderOptions();

public slots:
    void RenderMap();

private:
    Ui::RenderOptions *ui;
};

#endif // RENDEROPTIONS_H
