#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "whiteboard.h"
#include <QFile>
#include <QTextStream>
#include <QPainter>
#include <QShortcut>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), whiteboard(new Whiteboard) {
    ui->setupUi(this);
    setCentralWidget(whiteboard);
    QShortcut *setBlack = new QShortcut(QKeySequence(tr("1")), whiteboard);
    QShortcut *setRed = new QShortcut(QKeySequence(tr("2")), whiteboard);
    QShortcut *setGreen = new QShortcut(QKeySequence(tr("3")), whiteboard);
    QShortcut *setBlue = new QShortcut(QKeySequence(tr("4")), whiteboard);
    QShortcut *setYellow = new QShortcut(QKeySequence(tr("5")), whiteboard);
    connect(setBlack, &QShortcut::activated,
            whiteboard, [=] { whiteboard->setPenColor(Qt::black); });
    connect(setRed, &QShortcut::activated,
            whiteboard, [=] { whiteboard->setPenColor(Qt::red); });
    connect(setGreen, &QShortcut::activated,
            whiteboard, [=] { whiteboard->setPenColor(Qt::green); });
    connect(setBlue, &QShortcut::activated,
            whiteboard, [=] { whiteboard->setPenColor(Qt::blue); });
    connect(setYellow, &QShortcut::activated,
            whiteboard, [=] { whiteboard->setPenColor(Qt::yellow); });
}

MainWindow::~MainWindow() {
    delete ui;
}
