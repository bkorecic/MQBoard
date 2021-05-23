#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "whiteboard.h"
#include <QFile>
#include <QTextStream>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), whiteboard(new Whiteboard) {
    ui->setupUi(this);
    setCentralWidget(whiteboard);
}

MainWindow::~MainWindow() {
    delete ui;
}
