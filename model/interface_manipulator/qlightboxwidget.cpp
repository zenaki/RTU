#include "qlightboxwidget.h"

#include <QPixmap>
#include <QEvent>
#include <QPaintEvent>
#include <QChildEvent>
#include <QPainter>

QLightBoxWidget::QLightBoxWidget(QWidget* _parent, bool _folowToHeadWidget) :
	QWidget(_parent),
	m_isInUpdateSelf(false)
{
	//
    // The parent widget has to be necessarily installed
	//
	Q_ASSERT_X(_parent, "", Q_FUNC_INFO);

	//
    // If necessary, parents do the most "senior" widget
	//
	if (_folowToHeadWidget) {
		while (_parent->parentWidget() != 0) {
			_parent = _parent->parentWidget();
		}
		setParent(_parent);
	}

	//
    // Follow the events of the parent of the widget to
    // be able to redraw it, when you change the size, etc.
	//
	_parent->installEventFilter(this);

	//
    // hide the widget
	//
	setVisible(false);
}

bool QLightBoxWidget::eventFilter(QObject* _object, QEvent* _event)
{
	//
    // Widgets should always be the last child,
    // to overlap the rest of widgets when displayed
	//
	if (_event->type() == QEvent::ChildAdded) {
		QChildEvent* childEvent = dynamic_cast<QChildEvent*>(_event);
		if (childEvent->child() != this) {
			QWidget* parent = parentWidget();
//			setParent(0);
			setParent(parent);
		}
	}

	//
    // If you change the size of the parent widget,
    // you must repaint itself
	//
	if (isVisible()
		&& _event->type() == QEvent::Resize) {
		updateSelf();
	}
	return QWidget::eventFilter(_object, _event);
}

void QLightBoxWidget::paintEvent(QPaintEvent* _event)
{
	//
    // draw background
	//
	QPainter p;
	p.begin(this);
    // ... photo parent widget
	p.drawPixmap(0, 0, width(), height(), m_parentWidgetPixmap);
    // ... impose darkened area
	p.setBrush(QBrush(QColor(0, 0, 0, 220)));
	p.drawRect(0, 0, width(), height());
	p.end();

	//
    // Draw everything else
	//
	QWidget::paintEvent(_event);
}

void QLightBoxWidget::showEvent(QShowEvent* _event)
{
	//
    // refresh yourself
	//
	updateSelf();

	//
    // display
	//
	QWidget::showEvent(_event);
}

void QLightBoxWidget::updateSelf()
{
	if (!m_isInUpdateSelf) {
		m_isInUpdateSelf = true;

		{
			//
            // updating map
			//
			hide();
			resize(parentWidget()->size());
			m_parentWidgetPixmap = grabParentWidgetPixmap();
			show();
		}

		m_isInUpdateSelf = false;
	}
}

QPixmap QLightBoxWidget::grabParentWidgetPixmap() const
{
	QPixmap parentWidgetPixmap;

#if (QT_VERSION >= QT_VERSION_CHECK(5, 0, 0))
	parentWidgetPixmap = parentWidget()->grab();
#else
	parentWidgetPixmap = QPixmap::grabWidget(parentWidget());
#endif

	return parentWidgetPixmap;
}
