#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QTextCodec>
#include <CustomTabStyle.cpp>
#include <QFileDialog>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVBoxLayout>
#include <QMediaPlayer>
#include <QMessageBox>
#include <QShortcut>
#include <QSystemTrayIcon>
#include "NetworkController.h"
#include "capture.h"
#include "dictbean.h"
#include "tranbean.h"
#include "dict_simpbean.h"
#include "dict_webbean.h"
#include "dict_phrasebean.h"
#include "dict_examplebean.h"
#include "databasecontroller.h"
#include "ConnectPool.h"
#include "dict_edit.h"
#include "groupmanagment.h"
#include "dict_note_add_window.h"
#include "settingwindow.h"
#include "dict_preference_window.h"
#define TRAN_FROM_MAX_LENGTH 5000

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void noteInit();//初始化
    void tabBarInit(int);//tabbar初始化
    void noteTabinit(int index);
    void initKey();//初始化键盘事件
    void updateDict(dictBean bean);
    void updateTran(tranBean bean);

    bool eventFilter(QObject *watched, QEvent *e);

    void hideTranWidget();
    void showTranWidget();
    void showNoteTabbar(int);



    QString packUrlDict(QString);
    QMap<QString,QString> packUrlTran(QString);
private:
    Ui::MainWindow *ui;
    tranBean tranbean;
    dictBean dictbean;
    QList<newWordBean>list_newWord;


    QList<newWordBean>getNoteList(int index=0,QString keyword="");
    void updateNoteList(QList<newWordBean>);

    void updateNoteCard(int index=0);
    void updateNoteReview(int index=0);
public slots:


private slots:
    void tab_note_list_delete();//弹出菜单删除
    void tab_note_list_edit();//弹出菜单编辑
    void tab_note_list_move();//弹出菜单移动
    void tab_note_list_noreview();//弹出菜单不在复习
    void tab_note_list_setting_group();//添加组别
    void tab_note_list_setting_add();//添加单词
    void tab_note_list_setting_setting();//偏好设置
    void hideOrshow();//将窗口隐藏
    void systemIconEvent(QSystemTrayIcon::ActivationReason reason);

    void playAudio(QNetworkReply*reply);
    void dictFind(QNetworkReply*reply);
    void tranFind(QNetworkReply*reply);
    void updateList();
    void on_dict_button_back_clicked();
    void on_dict_find_clicked();
    void on_dict_doc_clicked();
    void on_dict_shot_clicked();
    void on_dict_button_pron_clicked();
    void on_dict_button_find_clicked();
    void on_tran_edit_from_textChanged();
    void on_tran_button_clear_clicked();
    void on_tran_button_tran_clicked();
    void on_tran_checkbox_clicked(bool checked);
    void on_tran_button_pron_clicked();
    void on_dict_button_add_clicked();

    void on_tab_note_button_card_clicked();
    void on_tab_note_button_list_clicked();
    void on_tab_note_button_review_clicked();
    void on_tab_note_card_pre_clicked();
    void on_tab_note_card_button_clicked();
    void on_tab_note_card_next_clicked();
    void on_tab_note_list_button_setting_clicked();
    void on_tab_note_review_button_clicked();
    void on_dict_edit_textChanged();
    void on_dict_edit_find_textChanged(const QString &arg1);
    void on_tab_note_card_button_setting_clicked();
    void on_tab_note_review_button_setting_clicked();

    void on_tab_note_list_button_sort_currentIndexChanged(int index);
    void on_tab_note_combox_group_currentIndexChanged(const QString &arg1);
    void on_tab_note_card_more_clicked();
    void on_tab_note_card_edit_clicked();
    void on_tab_note_review_more_clicked();
    void on_tab_note_review_edit_clicked();
    void on_tab_note_list_edit_find_textChanged(const QString &arg1);
    void on_tab_note_combox_group_currentIndexChanged(int index);
    void on_button_dict_clicked();
    void on_button_tran_clicked();
    void on_button_note_clicked();
    void on_button_doc_clicked();
    void on_button_interpret_clicked();
    void on_button_person_clicked();
    void on_button_class_clicked();
};

#endif // MAINWINDOW_H
