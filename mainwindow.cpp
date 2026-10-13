#include "mainwindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QMessageBox>
#include <QRegularExpression>
#include <QApplication>
#include <QFont>
#include <QPalette>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Resume Content & Skill Keyword Analyzer");
    resize(1000, 700);

    // Common technical skills checked by the analyzer
    skills = {
        "C++", "Java", "Python", "C", "SQL", "HTML", "CSS",
        "JavaScript", "React", "Spring Boot", "Git", "GitHub",
        "AWS", "Docker", "Linux", "MySQL", "Oracle",
        "Machine Learning", "Data Science", "PHP", "Node.js",
        "MongoDB", "Bootstrap", "Qt"
    };

    QWidget *central = new QWidget(this);
    setCentralWidget(central);

    QVBoxLayout *mainLayout = new QVBoxLayout(central);
    mainLayout->setSpacing(12);
    mainLayout->setContentsMargins(20, 15, 20, 15);

    // Title
    QLabel *title = new QLabel("RESUME CONTENT & SKILL KEYWORD ANALYZER");
    QFont titleFont("Arial", 18, QFont::Bold);
    title->setFont(titleFont);
    title->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(title);

    QLabel *subtitle = new QLabel(
        "Paste your resume below and click Analyze Resume to identify technical skills."
    );
    subtitle->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(subtitle);

    // Resume input
    QGroupBox *inputGroup = new QGroupBox("Resume Content");
    QVBoxLayout *inputLayout = new QVBoxLayout(inputGroup);

    resumeText = new QTextEdit();
    resumeText->setPlaceholderText(
        "Example:\n"
        "Rahul Kumar\n"
        "MCA Student\n\n"
        "Skills: C++, Java, Python, SQL, HTML, CSS, Git\n\n"
        "I have developed applications using C++ and Java. "
        "I have knowledge of MySQL and Spring Boot."
    );
    resumeText->setMinimumHeight(230);
    inputLayout->addWidget(resumeText);

    mainLayout->addWidget(inputGroup);

    // Buttons
    QHBoxLayout *buttonLayout = new QHBoxLayout();

    analyzeButton = new QPushButton("Analyze Resume");
    clearButton = new QPushButton("Clear");
    exitButton = new QPushButton("Exit");

    analyzeButton->setMinimumHeight(40);
    clearButton->setMinimumHeight(40);
    exitButton->setMinimumHeight(40);

    buttonLayout->addWidget(analyzeButton);
    buttonLayout->addWidget(clearButton);
    buttonLayout->addWidget(exitButton);

    mainLayout->addLayout(buttonLayout);

    // Summary labels
    QGridLayout *summaryLayout = new QGridLayout();

    wordCountLabel = new QLabel("Word Count: 0");
    skillCountLabel = new QLabel("Skills Found: 0");
    matchLabel = new QLabel("Keyword Match: 0%");

    QFont summaryFont("Arial", 11, QFont::Bold);
    wordCountLabel->setFont(summaryFont);
    skillCountLabel->setFont(summaryFont);
    matchLabel->setFont(summaryFont);

    summaryLayout->addWidget(wordCountLabel, 0, 0);
    summaryLayout->addWidget(skillCountLabel, 0, 1);
    summaryLayout->addWidget(matchLabel, 0, 2);

    mainLayout->addLayout(summaryLayout);

    matchProgress = new QProgressBar();
    matchProgress->setRange(0, 100);
    matchProgress->setValue(0);
    matchProgress->setFormat("Keyword Match: %p%");
    mainLayout->addWidget(matchProgress);

    // Result box
    QGroupBox *resultGroup = new QGroupBox("Analysis Result");
    QVBoxLayout *resultLayout = new QVBoxLayout(resultGroup);

    resultText = new QTextEdit();
    resultText->setReadOnly(true);
    resultText->setMinimumHeight(150);
    resultLayout->addWidget(resultText);

    mainLayout->addWidget(resultGroup);

    // Connections
    connect(analyzeButton, &QPushButton::clicked,
            this, &MainWindow::analyzeResume);

    connect(clearButton, &QPushButton::clicked,
            this, &MainWindow::clearResume);

    connect(exitButton, &QPushButton::clicked,
            this, &MainWindow::exitApplication);
}

int MainWindow::countWords(const QString &text)
{
    QString cleaned = text.trimmed();

    if (cleaned.isEmpty())
        return 0;

    QStringList words = cleaned.split(
        QRegularExpression("\\s+"),
        Qt::SkipEmptyParts
    );

    return words.size();
}

QStringList MainWindow::findSkills(const QString &text)
{
    QStringList foundSkills;

    for (const QString &skill : skills)
    {
        // Word-boundary style matching while allowing spaces and symbols
        QString pattern = QRegularExpression::escape(skill);

        QRegularExpression regex(
            "(^|[^A-Za-z0-9+#.])" + pattern +
            "([^A-Za-z0-9+#.]|$)",
            QRegularExpression::CaseInsensitiveOption
        );

        if (regex.match(text).hasMatch())
            foundSkills.append(skill);
    }

    return foundSkills;
}

void MainWindow::analyzeResume()
{
    QString text = resumeText->toPlainText();

    if (text.trimmed().isEmpty())
    {
        QMessageBox::warning(
            this,
            "No Resume",
            "Please enter or paste your resume first."
        );
        return;
    }

    int words = countWords(text);
    QStringList foundSkills = findSkills(text);

    int skillCount = foundSkills.size();

    // Percentage based on the number of detected skills
    // out of the complete predefined skill list.
    int matchPercentage = 0;

    if (!skills.isEmpty())
        matchPercentage = (skillCount * 100) / skills.size();

    wordCountLabel->setText(
        QString("Word Count: %1").arg(words)
    );

    skillCountLabel->setText(
        QString("Skills Found: %1").arg(skillCount)
    );

    matchLabel->setText(
        QString("Keyword Match: %1%").arg(matchPercentage)
    );

    matchProgress->setValue(matchPercentage);

    QString result;

    result += "<b>Detected Skills:</b><br>";

    if (foundSkills.isEmpty())
    {
        result += "No predefined technical skills were detected.<br>";
    }
    else
    {
        result += foundSkills.join(", ");
        result += "<br>";
    }

    result += "<br><b>Resume Statistics:</b><br>";
    result += QString("Total Words: %1<br>").arg(words);
    result += QString("Technical Skills Detected: %1<br>").arg(skillCount);
    result += QString("Keyword Match: %1%<br>").arg(matchPercentage);

    result += "<br><b>Suggestions:</b><br>";

    if (skillCount < 5)
    {
        result += "• Consider adding more relevant technical skills "
                  "if they genuinely match your experience.<br>";
    }
    else
    {
        result += "• Your resume contains several recognizable technical "
                  "skill keywords.<br>";
    }

    if (words < 100)
    {
        result += "• The resume text is quite short. Consider adding "
                  "projects, education, and experience details.<br>";
    }
    else
    {
        result += "• Resume length is sufficient for this basic analyzer.<br>";
    }

    resultText->setHtml(result);
}

void MainWindow::clearResume()
{
    resumeText->clear();
    resultText->clear();

    wordCountLabel->setText("Word Count: 0");
    skillCountLabel->setText("Skills Found: 0");
    matchLabel->setText("Keyword Match: 0%");
    matchProgress->setValue(0);
}

void MainWindow::exitApplication()
{
    QApplication::quit();
}
