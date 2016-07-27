#include "platos.h"
#include "ui_platos.h"
#include <QComboBox>
#include <QSpinBox>


platos::platos(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::platos)
{
  ui->setupUi(this);

  QStringList titles;
  titles<<"  Id_plato"<<"  Nombre  "<<" Precio "<<"Estado"<<"Cantidad";
   ui->tableWidget->setColumnCount(5);
   ui->tableWidget->setHorizontalHeaderLabels(titles);
start();
}
void platos::guardar_plato()
{
 ofstream ofs("platitos.txt");
 for(int i=0;i<index.size();i++)
       ofs<<to_string(index2[i])<<"\n"<<to_string(codes[i])<<"\n";
 ofs.close();
}

void platos::start()
{
  string consulta;
 QString nombrepl,preciopl;
 //consulta="select id_plato, nombre, precio, status from plato order by id_plato limit 40000";
 consulta="select * from mostrar_plato()";

 QString id,nombre,precio,estado;
  res=PQexec(conn,consulta.c_str());
 int cont, ntuples;
 for(cont=0, ntuples  = PQntuples(res);ntuples>0;ntuples--, cont++)
 {
     id= PQgetvalue(res,cont,0);nombre= PQgetvalue(res,cont,1);precio= PQgetvalue(res,cont,2);estado=PQgetvalue(res,cont,3);
        ui->tableWidget->insertRow(ui->tableWidget->rowCount());
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0 ,  new QTableWidgetItem(id));
        QSpinBox* spinbox= new QSpinBox(ui->tableWidget);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1 ,  new QTableWidgetItem(nombre));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2 ,  new QTableWidgetItem(precio));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3 ,  new QTableWidgetItem(estado));
        ui->tableWidget->setCellWidget(cont,4,spinbox);
 }
  PQclear(res);
}


void platos::on_buscar_plato_clicked()
{
  ui->tableWidget->setRowCount(0);
   QString nombrepl,preciopl;
   string snombrepl,spreciopl,consulta;
   nombrepl=ui->nombre->text();
   preciopl=ui->precio->text();
   snombrepl= nombrepl.toUtf8().constData();
   spreciopl= preciopl.toUtf8().constData();

  if(snombrepl==" ")  snombrepl="0";
  if(spreciopl==" ")  spreciopl="0";

  consulta="select id_plato, nombre, precio, status from plato where precio>='"+spreciopl+"' and nombre LIKE '%"+snombrepl+"%'";
//  ui->lineEdit->setText(QString::fromStdString(consulta));
   QString id,nombre,precio,estado;
    res=PQexec(conn,consulta.c_str());
   int cont, ntuples;
   for(cont=0, ntuples  = PQntuples(res);ntuples>0;ntuples--, cont++)
   {
         id= PQgetvalue(res,cont,0);nombre= PQgetvalue(res,cont,1);precio= PQgetvalue(res,cont,2);estado=PQgetvalue(res,cont,3);
          ui->tableWidget->insertRow(ui->tableWidget->rowCount());
          ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 0 ,  new QTableWidgetItem(id));
          ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1 ,  new QTableWidgetItem(nombre));
          ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2 ,  new QTableWidgetItem(precio));
          ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3 ,  new QTableWidgetItem(estado));
   }
   ui->nombre->setText("");ui->precio->setText("");
    PQclear(res);
}
void platos::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
  int indecito=item->row();
    index.push_back(indecito);
   QString ittemm= ui->tableWidget->item(indecito,0)->text();
  string str=ittemm.toUtf8().constData();
  index2.push_back(stoi(str));
  QSpinBox *spin = (QSpinBox*) ui->tableWidget->cellWidget(indecito,4);
  int code=spin->value();
  codes.push_back(code);
//  ui->lineEdit->setText(QString::number(code));
  guardar_plato();
}


void platos::on_aceptar_plato_clicked()
{
close();
}

platos::~platos()
{
  delete ui;
}
