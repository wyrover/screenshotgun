#ifndef EDITORFORM_H
#define EDITORFORM_H

#include <QWidget>
#include <QPushButton>
#include "modes/linemode.h"
#include "modes/rectmode.h"
#include "modes/visibleareamode.h"
#include "server.h"

class EditorView;

namespace Ui {
    class EditorForm;
}

class EditorForm : public QWidget
{
    Q_OBJECT

public:
    explicit EditorForm(EditorView*);
    ~EditorForm();
    AbstractMode* mode();
    EditorView* view();
    void setSelectedNext();
    void setSelectedPrevious();

    struct {
        VisibleAreaMode *visibleArea;
        LineMode *line;
        RectMode *rect;
    } modes;

private slots:
    void on_visibleAreaButton_clicked();
    void on_lineButton_clicked();
    void on_rectButton_clicked();
    void on_okButton_clicked();

private:
    void setSelected(QPushButton*);

    Ui::EditorForm *ui;
    EditorView* _editorView;
    AbstractMode* _mode;
    QLinkedList<QPushButton*> _buttons;
    QPushButton* _selected;
};

#endif // EDITORFORM_H
