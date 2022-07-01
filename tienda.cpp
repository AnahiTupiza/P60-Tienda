#include "tienda.h"
#include "ui_tienda.h"

#include <QDebug>

Tienda::Tienda(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Tienda)
{
    ui->setupUi(this);
    // Lista de productos
    cargarProductos();
    // Mostrar los productos en el combo
    foreach (Producto *p, m_productos){
        ui->inProducto->addItem(p->nombre());
    }
    // Configurar cabecera de la tabla
    QStringList cabecera = {"Cantidad", "Producto", "P. unitario", "Subtotal"};
    ui->outDetalle->setColumnCount(4);
    ui->outDetalle->setHorizontalHeaderLabels(cabecera);
    // Establecer el subtotal a 0
    m_subtotal = 0;
}

Tienda::~Tienda()
{
    delete ui;
}
/**
 * @brief Tienda::cargarProductos Carga la lista de productos de la tienda
 */
void Tienda::cargarProductos()
{
    // Crear productos "quemados" en el código
    m_productos.append(new Producto(1, "Leche", 0.80));
    m_productos.append(new Producto(2, "Pan", 0.15));
    m_productos.append(new Producto(3, "Queso", 2.50));
    // Podría leerse de una base de datos, de un archivo o incluso de Internet
}

bool Tienda::checkVacio()
{
    if(validarCedula(ui->inCedula->text())==true && ui->inCedula->text()!="9999999999"){

        ui->inCedula->setStyleSheet("QLineEdit{ background-color: green}");

        if(ui->inNombre->text()==""){
            ui->inNombre->setStyleSheet("QLineEdit{ background-color: orange}");
        }else{
            ui->inNombre->setStyleSheet("QLineEdit{ background-color: green}");
        }
        if(ui->inTelefono->text()==""){
            ui->inTelefono->setStyleSheet("QLineEdit{ background-color: orange}");
        }else{
            ui->inTelefono->setStyleSheet("QLineEdit{ background-color: green}");
        }
        if(ui->inEmail->text()==""){
            ui->inEmail->setStyleSheet("QLineEdit{ background-color: orange}");
        }else{
            ui->inEmail->setStyleSheet("QLineEdit{ background-color: green}");
        }
        if(ui->inDireccion->toPlainText()==""){
            ui->inDireccion->setStyleSheet("QPlainTextEdit {background-color: orange}");
        }else{
            ui->inDireccion->setStyleSheet("QPlainTextEdit {background-color: green}");
        }
        if(ui->inCedula->text()=="" || ui->inNombre->text()=="" || ui->inTelefono->text()=="" || ui->inEmail->text()==""||ui->inDireccion->toPlainText()==""){
            return false;
        }
        if(ui->inCedula->text()!="" && ui->inNombre->text()!="" && ui->inTelefono->text()!="" && ui->inEmail->text()!="" && ui->inDireccion->toPlainText()!=""){
            return true;
        }
    }else if(ui->inCedula->text()=="9999999999"){
        return true;
    }else{
        if(validarCedula(ui->inCedula->text())==false){
            ui->inCedula->setStyleSheet("QLineEdit{ background-color: orange}");
            return false;
        }
    }
    return true;
}

void Tienda::enviarDatosdeCompra()
{
    int filas=ui->outDetalle->rowCount();
    QString detalles="";
    while(contador!=filas){
        detalles+="\t"+ui->outDetalle->item(contador,0)->text()+"\t   "+
                ui->outDetalle->item(contador,1)->text()+"\t          "+
                ui->outDetalle->item(contador,2)->text()+"\t                  "+
                ui->outDetalle->item(contador,3)->text()+"\t\t\n";

        contador++;
    }
    m_detalles=detalles;

}

void Tienda::calcular(float stProducto)
{
    // Calcular valores
    m_subtotal += stProducto;
    float iva = m_subtotal * IVA / 100;
    float total = m_subtotal + iva;
    // Mostrar valores en GUI
    ui->outSubtotal->setText("$ " + QString::number(m_subtotal, 'f', 2));
    ui->outIva->setText("$ " + QString::number(iva, 'f', 2));
    ui->outTotal->setText("$ " + QString::number(total, 'f', 2));
}

void Tienda::limpiar()
{
    ui->inCedula->setText("");
    ui->inNombre->setText("");
    ui->inTelefono->setText("");
    ui->inEmail->setText("");
    ui->inDireccion->setPlainText("");
    int rows=ui->outDetalle->rowCount();
    while(rows!=-1){
        ui->outDetalle->removeRow(rows);
        rows--;
    }
    ui->outDetalle->removeRow(0);
    ui->outDetalle->removeRow(0);
    ui->outDetalle->removeRow(0);
    m_subtotal=0;
    iva=0;
    total=0;
    ui->outSubtotal->setText("$ 0.00");
    ui->outIva->setText("$ 0.00");
    ui->outTotal->setText("$ 0.00");
    ui->inCedula->setStyleSheet("QLineEdit{ background-color: white}");
    ui->inNombre->setStyleSheet("QLineEdit{ background-color: white}");
    ui->inTelefono->setStyleSheet("QLineEdit{ background-color: white}");
    ui->inEmail->setStyleSheet("QLineEdit{ background-color: white}");
    ui->inDireccion->setStyleSheet("QPlainTextEdit {background-color: white}");
    m_detalles="";
    contador=0;
}

bool Tienda::validarCedula(QString as)
{
    bool est = true;
    int vcedula[10];
    int vPar[4];
    int vImpar[5]={0};
    int sumaPar=0;
    int sumaImpar=0;
    int total;
    int nveri;

    double nu;

    if(as=="9999999999"){
        return true;
    }

    do
    {

        nu=as.toInt();
        if(nu<100000000 || nu>9999999999)
        {

            est=false;
            break;
        }


        //Separar string
        QString p1=as.mid(0,1);
        QString p2=as.mid(1,1);
        QString p3=as.mid(2,1);
        QString p4=as.mid(3,1);
        QString p5=as.mid(4,1);
        QString p6=as.mid(5,1);
        QString p7=as.mid(6,1);
        QString p8=as.mid(7,1);
        QString p9=as.mid(8,1);
        QString p10=as.mid(9,1);

        //Transformar string
        vcedula[0]=p1.toInt();
        vcedula[1]=p2.toInt();
        vcedula[2]=p3.toInt();
        vcedula[3]=p4.toInt();
        vcedula[4]=p5.toInt();
        vcedula[5]=p6.toInt();
        vcedula[6]=p7.toInt();
        vcedula[7]=p8.toInt();
        vcedula[8]=p9.toInt();
        vcedula[9]=p10.toInt();

        if(vcedula[0]>2)
        {

            est = false;
            break;
        }

        //Pares
        vPar[0]=vcedula[1];
        vPar[1]=vcedula[3];
        vPar[2]=vcedula[5];
        vPar[3]=vcedula[7];
        //Impares
        vImpar[0]=vcedula[0];
        vImpar[1]=vcedula[2];
        vImpar[2]=vcedula[4];
        vImpar[3]=vcedula[6];
        vImpar[4]=vcedula[8];


        //Multiplicacion impar
        for(int i=0; i<5; i++)
        {
            vImpar[i]=vImpar[i]*2;
            if(vImpar[i]>9)
            {
                vImpar[i]=vImpar[i]-9;
            }
            sumaImpar += vImpar[i];
        }
        //Sumar los pares
        for(int i=0; i<4; i++)
        {
            sumaPar += vPar[i];
        }

        total = sumaPar + sumaImpar;

        //Se obtiene el modulo

        nveri = total%10;


        //Numero verificador
        if(nveri==0)
        {
            if(nveri==vcedula[9])
            {
                est=true;
                break;
            }else
            {
                est=false;
                break;
            }
        }else if(nveri !=0)
        {
            nveri=10-nveri;

            if(nveri==vcedula[9])
            {
                est=true;
                break;
            }else
            {

                est=false;
                break;
            }
        }

    }while(nu<100000000 || nu>9999999999 || vcedula[0]>2);
    return est;
}


void Tienda::on_inProducto_currentIndexChanged(int index)
{
    // Obtener el precio del producto actual seleccionado
    float precio = m_productos.at(index)->precio();
    // Mostrar el precio del product en la etiqueta
    ui->outPrecio->setText("$ " + QString::number(precio,'f',2));
    // Resetear el spinbox de cantidad
    ui->inCantidad->setValue(0);
}


void Tienda::on_btnAgregar_released()
{
    // Validar que no se agregen productos cpn 0 cantidad
    int cantidad = ui->inCantidad->value();
    if (cantidad == 0){
        return;
    }
    // Obtener los datos de la GUI
    int i = ui->inProducto->currentIndex();
    Producto *p = m_productos.at(i);

    // Calcular el subrotal del producto
    float subtotal = p->precio() * cantidad;

    // Agregar los datos a la tabla
    int fila = ui->outDetalle->rowCount();
    ui->outDetalle->insertRow(fila);
    ui->outDetalle->setItem(fila, 0, new QTableWidgetItem(QString::number(cantidad)));
    ui->outDetalle->setItem(fila, 1, new QTableWidgetItem(p->nombre()));
    ui->outDetalle->setItem(fila, 2, new QTableWidgetItem(QString::number(p->precio(),'f',2)));
    ui->outDetalle->setItem(fila, 3, new QTableWidgetItem(QString::number(subtotal,'f',2)));

    // Limpiar datos
    ui->inCantidad->setValue(0);
    ui->inProducto->setFocus();

    // Actualizar subtotales
    calcular(subtotal);

}

void Tienda::on_btnFacturar_pressed()
{
    if(checkVacio()==true){

        Factura *factura=new Factura(this);
        enviarDatosdeCompra();
        if(ui->inCedula->text()!="9999999999"){
            factura->datosFactura(ui->inCedula->text(),ui->inNombre->text(),
                                  ui->inTelefono->text(),ui->inEmail->text(),
                                  ui->inDireccion->toPlainText(),m_detalles);
        }else{
            QString nombre= "Consumidor Final";
            QString telefono="**********";
            QString email="***********@gmail.com";
            QString direccion="***************";
            factura->datosFactura(ui->inCedula->text(),nombre,
                                  telefono,email,
                                  direccion,m_detalles);
        }


        factura->ValoresFactura(m_subtotal,iva,total);
        if(contador !=0){
            factura->cargarDatos();
            factura->exec();
            limpiar();
        }

    }
}






