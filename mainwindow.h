#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;  // Обработка закрытия

private slots:
    //Кнопки для перехода к тексту заданий
    void on_buttonMain_whattask1_clicked();
    void on_buttonMain_whattask2_clicked();
    void on_buttonMain_whattask3_clicked();
    void on_buttonMain_whattask4_clicked();
    void on_buttonMain_whattask5_clicked();

    //Кнопки для перехода к заданиям
    void on_buttonMain_task1_clicked();
    void on_buttonMain_task2_clicked();
    void on_buttonMain_task3_clicked();
    void on_buttonMain_task4_clicked();
    void on_buttonMain_task5_clicked();

    void updateDateTime();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
