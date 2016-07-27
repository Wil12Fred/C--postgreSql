#ifndef CLIENTE_H
#define CLIENTE_H

#include <QMainWindow>
#include<mainwindow.h>
#include<pedido.h>
#include <QTableWidgetItem>
using namespace std;
namespace Ui {
  class Cliente;
}

class Cliente :public QMainWindow
{
  Q_OBJECT

public:
  explicit Cliente(QWidget *parent = 0);
  ~Cliente();
  PGconn    *conn= PQconnectdb("dbname=Restaurant host=localhost user=postgres password='ltch23. '");
  PGresult  *res;
  int index;
  void guardar2();
  void start();
private slots:
  void on_aceptar_cliente_clicked();
  void on_buscar_cliente_clicked();
  void on_tableWidget_itemClicked(QTableWidgetItem *item);

  void on_cerrar_clicked();

private:
  Ui::Cliente *ui;
};

#endif // CLIENTE_H
