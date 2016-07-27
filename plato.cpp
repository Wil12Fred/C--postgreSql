#include "plato.h"
#include "ui_plato.h"
#include <QTableWidgetItem>
#include <QTableWidget>
#include <vector>
#include <string>
using namespace std;

Plato::Plato(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Plato)
{
    ui->setupUi(this);

     conn= PQconnectdb("dbname=Restaurant host=localhost user=postgres password='ltch23. '");
    QStringList titles;
    titles<<"  Id_plato"<<"  Nombre  "<<" Precio "<<"Estado";
     ui->tableWidget->setColumnCount(4);
     ui->tableWidget->setHorizontalHeaderLabels(titles);

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
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 1 ,  new QTableWidgetItem(nombre));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 2 ,  new QTableWidgetItem(precio));
            ui->tableWidget->setItem(ui->tableWidget->rowCount()-1, 3 ,  new QTableWidgetItem(estado));
     }
      PQclear(res);
 }


Plato::~Plato()
{
    delete ui;
}

void Plato::on_tableWidget_itemClicked(QTableWidgetItem *item)
{
 int it=item->row();
index2.push_back(it);
 QString ittemm= ui->tableWidget->item(it,0)->text();
string str=ittemm.toUtf8().constData();
index.push_back(stoi(str));
}

void Plato::on_pushButton_clicked()
{
    ui->tableWidget->setRowCount(0);
    QString nombrepl,preciopl;
    string snombrepl,spreciopl,consulta;
    nombrepl=ui->nombrepl->text();
    preciopl=ui->preciopl->text();
    snombrepl= nombrepl.toUtf8().constData();
    spreciopl= preciopl.toUtf8().constData();

    //if(snombrepl=="") consulta="select id_plato, nombre, precio, status from plato where precio>='"+spreciopl+"' order by id_plato limit 40000";
    if(snombrepl=="") consulta="select* from buscar_por_precio('"+spreciopl+"')";
    else consulta="select * from buscar_platos('"+snombrepl+"',"+"'"+spreciopl+"')";
    //else   consulta="select id_plato, nombre, precio , status from plato where nombre='"+snombrepl+"' and precio>='"+spreciopl+"' order by id_plato limit 40000";

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
     PQclear(res);
}

void Plato::on_pushButton_2_clicked()
{
string remove,number;
  for( int i=0;i<index.size();i++)
    {
     number=to_string(index[i]);
     remove="UPDATE plato set status=false where id_plato='"+number+"'";
     res=PQexec(conn,remove.c_str());
    }
  QString tmp2=QString::number(stoi(number));
  //ui->lineEdit->setText(tmp2);
}

void Plato::on_pushButton_3_clicked()
{
    vector<QString> list, list2;
    string update ,update2,number,tmp,tmp2;
    for(int i=0;i<index.size();i++)
     {
        list.push_back(ui->tableWidget->item(index2[i],2)->text());
        list2.push_back(ui->tableWidget->item(index2[i],1)->text());
      }
  for(int i=0;i<list.size();i++)
    {
      tmp=list[i].toUtf8().constData();
      tmp2=list2[i].toUtf8().constData();
      number=to_string(index[i]);
      //update="UPDATE plato set precio='"+tmp+"' where id_plato='"+number+"'";
      update="select actualizar_precio_plato('"+tmp+"','"+number+"')";
      //update2="UPDATE plato set nombre='"+tmp2+"' where id_plato='"+number+"'";
      update2="select actualizar_nombre_plato('"+tmp2       +"','"+number+"')";
      res=PQexec(conn,update.c_str());
      res=PQexec(conn,update2.c_str());
    }

    //ui->lineEdit_2->setText(QString::number(index[0]));
  //ui->lineEdit->setText(QString::fromStdString(update));
}

void Plato::on_pushButton_4_clicked()
{
  close();
}

void Plato::on_pushButton_5_clicked()
{
    QString agrenombre,agreprecio;
    string insertar;
    string sagrenombre,sagreprecio;
    agrenombre=ui->agrenombre->text();
    agreprecio=ui->agreprecio->text();
    sagrenombre=agrenombre.toUtf8().constData();
    sagreprecio=agreprecio.toUtf8().constData();
    if(!sagrenombre.empty() && !sagreprecio.empty())
    {
        //insertar="insert into plato(nombre,precio,status) values ('"+sagrenombre+"','"+sagreprecio+"','true')";
        insertar="select insertar_plato('"+sagrenombre+"','"+sagreprecio+"')";
        res=PQexec(conn,insertar.c_str());

    }
}
