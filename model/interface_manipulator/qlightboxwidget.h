#ifndef QLIGHTBOXWIDGET_H
#define QLIGHTBOXWIDGET_H

#include <QWidget>


/**
 * @brief overlap class
 */
class QLightBoxWidget : public QWidget
{
	Q_OBJECT

public:
	explicit QLightBoxWidget(QWidget* _parent, bool _folowToHeadWidget = false);

protected:
	/**
     * @brief It is overridden to track parent widget events
	 */
	bool eventFilter(QObject* _object, QEvent* _event);

	/**
     * @brief Redefined in order to simulate the effect of overlap
	 */
	void paintEvent(QPaintEvent* _event);

	/**
     * @brief It is overridden to before displaying customize the appearance
	 */
	void showEvent(QShowEvent* _event);

private:
	/**
     * @brief Reload size and background image
	 */
	void updateSelf();

	/**
     * @brief Resolve conflicts recursive updates
	 */
	bool m_isInUpdateSelf;

	/**
     * @brief Reload background image
	 */
	QPixmap grabParentWidgetPixmap() const;

	/**
     * @brief background Image
	 */
	QPixmap m_parentWidgetPixmap;
};

#endif // QLIGHTBOXWIDGET_H
