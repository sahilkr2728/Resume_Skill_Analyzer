#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QListWidget>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void analyzeResume();
    void clearResume();
    void exitApplication();

private:
    QTextEdit *resumeText;
    QTextEdit *resultText;
    QLabel *wordCountLabel;
    QLabel *skillCountLabel;
    QLabel *matchLabel;
    QProgressBar *matchProgress;
    QPushButton *analyzeButton;
    QPushButton *clearButton;
    QPushButton *exitButton;

    QStringList skills;

    int countWords(const QString &text);
    QStringList findSkills(const QString &text);
};

#endif // MAINWINDOW_H
