#include "renderoptions.h"
#include "ui_renderoptions.h"

RenderOptions::RenderOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RenderOptions)
{
    ui->setupUi(this);

    this->connect(ui->actionStartRender, SIGNAL(triggered()), this, SLOT(RenderMap()));
}

RenderOptions::~RenderOptions()
{
    delete ui;
}

void RenderOptions::RenderMap()
{
    QFileDialog fd;

    fd.setFileMode(QFileDialog::Directory);

    QStringList fileNames;
    if (fd.exec())
    {
        fileNames = fd.selectedFiles();

        ui->Info->setText("Rendering...");

        Chunk::RenderMode mode = Chunk::TOP_DOWN_LOW_RES;

        void *params = NULL;

        float alpha = 0;

        if(ui->TopDown->isChecked())
        {
            if(ui->Normal->isChecked())
            {
                mode = Chunk::TOP_DOWN_LOW_RES;
            }
            else if(ui->HeightMap->isChecked())
            {
                mode = Chunk::TOP_DOWN_LOW_RES_HEIGHT;
            }
            else if(ui->LightMap->isChecked())
            {
                mode = Chunk::CAVES_LOW_RES_LIGHT;
            }
        }
        else if(ui->Caves->isChecked())
        {
            alpha = (float)QInputDialog::getDouble(this, "Blending", "Blend Percentage: ", 0, 0, 1.0);
            if(ui->Normal->isChecked())
            {
                mode = Chunk::CAVES_LOW_RES;
            }
            else if(ui->HeightMap->isChecked())
            {
                mode = Chunk::CAVES_LOW_RES_HEIGHT;
            }
            else if(ui->LightMap->isChecked())
            {
                mode = Chunk::CAVES_LOW_RES_LIGHT;
            }

            params = &alpha;
        }

        Map m(fileNames[0].toStdString(), mode, params);

        m.SaveImage(QFileDialog::getSaveFileName(this, "Save Image", QString(), tr("Images (*.png *.tga *.gif *.jpg)")).toStdString());

        ui->Info->setText("Done.");
    }
}
