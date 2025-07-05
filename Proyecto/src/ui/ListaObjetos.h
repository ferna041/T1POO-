#ifndef LISTAOBJETOS_H
#define LISTAOBJETOS_H

#include <QWidget>
#include <QPushButton>
#include "DatabaseManager.h"
#include "Objeto.h"

namespace Ui {
class ListaObjetos;
}

class ListaObjetos : public QWidget
{
    Q_OBJECT

public:
    explicit ListaObjetos(QWidget *parent = nullptr);
    explicit ListaObjetos(int usuarioId, bool mostrarSoloMisObjetos = false, QWidget *parent = nullptr);
    ~ListaObjetos();

private slots:
    void on_pushButtonActualizar_clicked();
    void cargarObjetos();
    void reservarObjeto();

private:
    void configurarTabla();

    Ui::ListaObjetos *ui;
    DatabaseManager *db;
    int usuarioActualId;
    bool mostrarSoloMisObjetos;
};

#endif // LISTAOBJETOS_H
