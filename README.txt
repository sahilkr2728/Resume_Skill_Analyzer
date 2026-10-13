RESUME CONTENT AND SKILL KEYWORD ANALYZER
============================================

Language:
C++

GUI Framework:
Qt Widgets

IDE:
Qt Creator

PROJECT DESCRIPTION:
This mini project analyzes resume text entered by the user.
It searches the resume for predefined technical skill keywords
and displays basic resume statistics.

FEATURES:
1. Resume text input
2. Technical skill detection
3. Word count
4. Number of detected skills
5. Keyword match percentage
6. Suggestions
7. Clear button
8. Exit button

SKILLS CHECKED:
C++, Java, Python, C, SQL, HTML, CSS, JavaScript, React,
Spring Boot, Git, GitHub, AWS, Docker, Linux, MySQL, Oracle,
Machine Learning, Data Science, PHP, Node.js, MongoDB,
Bootstrap and Qt.

HOW TO RUN:
1. Install Qt and Qt Creator.
2. Open ResumeSkillAnalyzer.pro in Qt Creator.
3. Select a Desktop Qt Kit.
4. Click Build.
5. Click Run.
6. Paste a resume into the text area.
7. Click "Analyze Resume".

IMPORTANT:
This is a basic educational mini project. It uses keyword matching,
not artificial intelligence or a real ATS algorithm.

PROJECT FLOW:
User enters resume
       |
       v
Read resume text
       |
       v
Count words
       |
       v
Search predefined skill keywords
       |
       v
Calculate basic keyword percentage
       |
       v
Display analysis

VIVA EXPLANATION:
"The project is developed in C++ using Qt Widgets. The user enters
resume content in a QTextEdit. When the Analyze button is clicked,
the program reads the text, counts words, and checks the text against
a predefined list of technical skills. QRegularExpression is used
for case-insensitive keyword matching. The detected skills and basic
statistics are then displayed in the GUI."

NOTE ABOUT KEYWORD MATCH:
The percentage represents detected skills compared with the project's
predefined skill list. It is an educational metric and is not an
industry-standard ATS score.
