#ifndef CAPTURE_H
#define CAPTURE_H

#include <QWidget>
#include <QPainter>
// 矩形选中区边框宽度;
#define SELECT_RECT_BORDER_WIDTH                1

// 选中矩形8个拖拽点小矩形的宽高;
#define STRETCH_RECT_WIDTH                      6
#define STRETCH_RECT_HEIGHT                     6

// 选中矩形信息矩形的宽高;
#define SELECT_RECT_INFO_WIDTH                  75
#define SELECT_RECT_INFO_HEIGHT                 20

// 选区矩形的右下顶点放大图的宽高;
#define END_POINT_RECT_WIDTH                    122
#define END_POINT_RECT_HEIGHT                   122
#define END_POINT_IMAGE_HEIGHT                  90

enum CaptureState{
    InitCapture = 0,
    BeginCaptureImage,
    FinishCaptureImage,
    BeginMoveCaptureArea,
    FinishMoveCaptureArea,
    BeginMoveStretchRect,
    FinishMoveStretchRect
}; //进行截屏的状态;

enum StretchRectState{
    NotSelect = 0,
    TopLeftRect,
    TopRightRect,
    BottomLeftRect,
    BottomRightRect,
    LeftCenterRect,
    TopCenterRect,
    RightCenterRect,
    BottomCenterRect
};// 当前鼠标所在顶点状态;


class Capture : public QWidget
{
    Q_OBJECT
Q_SIGNALS:
    // 通知截图完毕，并将截取图片传递给调用类;
    void signalCompleteCature(QPixmap catureImage);

public:
    explicit Capture(QWidget *parent = 0);
    ~Capture();

private:

    void initWindow();
    void initStretchRect();
    void loadBackgroundPixmap();
    QRect getRect(const QPoint &beginPoint, const QPoint &endPoint);
    QRect getMoveRect();
    QRect getStretchRect();
    bool isPressPointInSelectRect(QPoint mousePressPoint);
    QRect getSelectRect();
    QPoint getMovePoint();
    StretchRectState getStrethRectState(QPoint point);
    void setStretchCursorStyle(StretchRectState stretchRectState);

    void drawCaptureImage();
    void drawStretchRect();
    void drawSelectRectInfo();
    void drawEndPointImage();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void paintEvent(QPaintEvent *event);


    QPixmap m_loadPixmap, m_capturePixmap;
    int m_screenwidth;
    int m_screenheight;
    // 保存确定选区的坐标点;
    QPoint m_beginPoint, m_endPoint, m_beginMovePoint, m_endMovePoint;
    QPainter m_painter;
    // 保存当前截图状态;
    CaptureState m_currentCaptureState;
    // 当前选择区域矩形;
    QRect m_currentSelectRect;
    // 选中矩形8个顶点小矩形;
    QRect m_topLeftRect, m_topRightRect, m_bottomLeftRect, m_bottomRightRect;
    QRect m_leftCenterRect, m_topCenterRect, m_rightCenterRect, m_bottomCenterRect;
    // 当前鼠标所在顶点状态;
    StretchRectState m_stretchRectState;
};

#endif // CAPTURE_H
