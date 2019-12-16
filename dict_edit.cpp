#include "dict_edit.h"
#include "ui_dict_edit.h"

dict_edit::dict_edit(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::dict_edit)
{
    ui->setupUi(this);

}

dict_edit::~dict_edit()
{
    delete ui;
}

QString dict_edit::getName() const
{
    return name;
}

void dict_edit::setName(const QString &name)
{
    this->name=name;
}

void dict_edit::closeEvent(QCloseEvent *closeEvent)
{

    emit updateList();
}

dict_edit::dict_edit(QWidget *parent, QString name):
    QMainWindow(parent),
    ui(new Ui::dict_edit)
{
    ui->setupUi(this);
    this->name=name;
    if(!name.isEmpty())
        ui->dict_edit_edit_dict->setText(name);

    connect(this,SIGNAL(updateList()),parent,SLOT(updateList()));

    //获取单词本中单词
    QSqlDatabase database=ConnectPool::openConnection();
    databaseController controller=databaseController::getInstance(database);
    newWordBean bean=controller.getNewWordByName(name);
    ui->dict_edit_edit_mask->setText(bean.getSoundMark());
    ui->dict_edit_edit_explain->setText(bean.getExplain());
    //分组信息未实现

    ConnectPool::closeConnection(database);
}

void dict_edit::on_dict_edit_button_dict_clicked()
{
    if(name.isEmpty())
        return;
    //删除单词
    QSqlDatabase database=ConnectPool::openConnection();
    databaseController controller=databaseController::getInstance();
    controller.deleteNewWord(name);
    ConnectPool::closeConnection(database);
    this->close();
}

void dict_edit::on_dict_edit_button_sure_clicked()
{
    //更新信息
    if(name.isEmpty())
        return;
    //更新单词
    QSqlDatabase database=ConnectPool::openConnection();
    databaseController controller=databaseController::getInstance();
    int r=controller.updateNewword(newWordBean(ui->dict_edit_edit_dict->text(),ui->dict_edit_combox_group->currentText(),
    ui->dict_edit_edit_mask->text(),ui->dict_edit_edit_explain->toPlainText()));

    ConnectPool::closeConnection(database);
    this->close();
}

void dict_edit::on_dict_edit_button_cancel_clicked()
{
    //关闭窗体
    this->close();
}
