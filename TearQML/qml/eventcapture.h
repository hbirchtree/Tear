#ifndef EVENTCAPTURE
#define EVENTCAPTURE

#include <QQuickItem>
class TearInputField : public QQuickItem {
    Q_PROPERTY(bool active READ active WRITE setActive)
    Q_PROPERTY(bool captureMouse READ captureMouse WRITE setCaptureMouse)
    Q_PROPERTY(bool captureKeys READ captureKeys WRITE setCaptureKeys)
    Q_PROPERTY(bool tapClick READ tapClick WRITE setTapClick)

    Q_PROPERTY(QRect mouseArea READ mouseArea WRITE setMouseArea)
    Q_PROPERTY(QRect screenArea READ screenArea WRITE setScreenArea)

    Q_OBJECT
public:
    TearInputField() :
    m_captureKeys(true),
    m_captureMouse(true),
    m_tapClick(true),
    m_mouseArea(QRect(0,0,1,1)),
    m_screenArea(QRect(0,0,1,1)){
        setAcceptedMouseButtons(Qt::AllButtons);
        setAcceptHoverEvents(true);
    }
    bool captureKeys() const{
        return m_captureKeys;
    }
    bool captureMouse() const{
        return m_captureMouse;
    }
    bool active() const{
        return m_active;
    }
    bool tapClick() const{
        return m_tapClick;
    }
    QRect mouseArea() const{
        return m_mouseArea;
    }
    QRect screenArea() const{
        return m_screenArea;
    }

public slots:
    void setCaptureKeys(bool captureKeys){
        m_captureKeys = captureKeys;
    }
    void setCaptureMouse(bool captureMouse){
        m_captureMouse = captureMouse;
    }
    void setActive(bool active){
        if (m_active == active) return;
        m_active = active;
    }
    void setTapClick(bool tapClick){
        m_tapClick = tapClick;
    }
    void setMouseArea(QRect mouseArea){
        m_mouseArea = mouseArea;
    }
    void setScreenArea(QRect screenArea){
        m_screenArea = screenArea;
    }

private:
    QPoint scaleMouse(const QPoint& pos){
        if(screenArea().width()<1||screenArea().height()<1)
            return pos;
        QPoint npos;
        npos.setX(pos.x()*(float)mouseArea().width()/(float)screenArea().width());
        npos.setY(pos.y()*(float)mouseArea().height()/(float)screenArea().height());
        return npos;
    }
    QPoint offsetMouse(const QPoint& pos){
        QPoint npos;
        npos.setX(pos.x()+mouseArea().x()-screenArea().x());
        npos.setY(pos.y()+mouseArea().y()-screenArea().y());
        return npos;
    }
    bool checkBound(const QPoint& pos){
        return pos.x()>=mouseArea().topLeft().x()&&
                pos.y()>=mouseArea().topLeft().y()&&
                pos.x()<=mouseArea().bottomRight().x()&&
                pos.y()<=mouseArea().bottomRight().y();
    }

    void keyPressEvent(QKeyEvent *event){
        if(!event->isAutoRepeat()&&captureKeys())
            newEvent(event->type(),event->key(),event->modifiers());
    }
    void keyReleaseEvent(QKeyEvent *event){
        if(!event->isAutoRepeat()&&captureKeys())
            newEvent(event->type(),event->key(),event->modifiers());
    }
    void hoverMoveEvent(QHoverEvent *event){
        if(!tapClick()){
            QPoint mpos = scaleMouse(offsetMouse(event->pos()));
            if(checkBound(mpos))
                newEvent(QEvent::TabletMove,mpos.x(),mpos.y());
        }
    }
    void mouseMoveEvent(QMouseEvent *event){
        if(!tapClick()){
            QPoint mpos = scaleMouse(offsetMouse(event->pos()));
            if(checkBound(mpos))
                newEvent(QEvent::TabletMove,mpos.x(),mpos.y());
        }else{
            QPoint mpos = scaleMouse(event->pos()-lastMousePos);
            newEvent(QEvent::TabletMove,mpos.x(),mpos.y());
            lastMousePos = event->pos();
        }
    }
    void mousePressEvent(QMouseEvent *event){
        if(!tapClick()){
            newEvent(event->type(),event->button(),0);
        }else
            lastMousePos = event->pos();
    }
    void mouseReleaseEvent(QMouseEvent *event){
        if(!tapClick())
            newEvent(event->type(),event->button(),0);
    }
    void mouseDoubleClickEvent(QMouseEvent *event){
        if(tapClick()){
            newEvent(QMouseEvent::MouseButtonPress,event->button(),0);
            newEvent(QMouseEvent::MouseButtonRelease,event->button(),0);
        }
    }
    void wheelEvent(QWheelEvent *event){
        newEvent(event->type(),event->angleDelta().x(),event->angleDelta().y());
    }

    QPoint lastMousePos;
    bool m_captureKeys;
    bool m_captureMouse;
    bool m_active;
    bool m_tapClick;
    QRect m_mouseArea;
    QRect m_screenArea;

signals:
    void newEvent(int type, int v1,int v2);
};

#endif // EVENTCAPTURE

