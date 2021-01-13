#include "LightBaseWidget.h"
#include "LightBaseRenderWidget.h"
#include "CustomCombineControl/UICustomVec3Control.h"
#include "CustomCombineControl/UICustomDoubleControl.h"
#include <QVBoxLayout>
#include <QPushButton>

LightBaseWidget::LightBaseWidget(QWidget* parent)
    :QWidget(parent)
{
    QVBoxLayout* pLayout = new QVBoxLayout(this);
    pLayout->setMargin(2);
    pLayout->setSpacing(2);

    m_pRenderWidget = new LightBaseRenderWidget;
    m_pRenderWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    pLayout->addWidget(m_pRenderWidget);

    m_pPosVec3Control = new UICustomVec3Control;
    m_pPosVec3Control->setColumnWidth(0, 230);
    m_pPosVec3Control->setRange(-10000.0f, 10000.0f);
    m_pPosVec3Control->setValue(m_pRenderWidget->getCameraPostion());
    m_pPosVec3Control->setTagText(tr("Camera Postion: "));
    pLayout->addWidget(m_pPosVec3Control);
    QObject::connect(m_pPosVec3Control, &UICustomVec3Control::valueChanged, this, &LightBaseWidget::onCameraPostionChanged);

    m_pFrontVec3Control = new UICustomVec3Control;
    m_pFrontVec3Control->setColumnWidth(0, 230);
    m_pFrontVec3Control->setRange(-10000.0f, 10000.0f);
    m_pPosVec3Control->setValue(m_pRenderWidget->getCameraFront());
    m_pFrontVec3Control->setTagText(tr("Camera Direction: "));
    pLayout->addWidget(m_pFrontVec3Control);
    QObject::connect(m_pFrontVec3Control, &UICustomVec3Control::valueChanged, this, &LightBaseWidget::onCameraFrontControlValueChanged);

    m_pPerspAngleControl = new UICustomDoubleControl;
    m_pPerspAngleControl->setColumnWidth(0, 230);
    m_pPerspAngleControl->setRangeValue(1.0f, 45.0f);
    m_pPerspAngleControl->setCurrentValue(m_pRenderWidget->getProjMatrixAngle());
    m_pPerspAngleControl->setTagText(tr("Perspective Angle: "));
    pLayout->addWidget(m_pPerspAngleControl);
    QObject::connect(m_pPerspAngleControl, &UICustomDoubleControl::valueChanged, this, &LightBaseWidget::onProjMatrixAngleControlValueChanged);

    QObject::connect(m_pRenderWidget, &LightBaseRenderWidget::cameraPostionChanged, this, &LightBaseWidget::onCameraPostionChanged);
    QObject::connect(m_pRenderWidget, &LightBaseRenderWidget::cameraFrontChanged, this, &LightBaseWidget::onCameraFrontChanged);
    QObject::connect(m_pRenderWidget, &LightBaseRenderWidget::projMatrixAngleChanged, this, &LightBaseWidget::onProjMatrixAngleChanged);
}

LightBaseWidget::~LightBaseWidget()
{

}

void LightBaseWidget::onCameraPostionChanged(const QVector3D& vec)
{
    m_pPosVec3Control->blockSignals(true);
    m_pPosVec3Control->setValue(vec);
    m_pPosVec3Control->blockSignals(false);
}

void LightBaseWidget::onCameraFrontChanged(const QVector3D& vec)
{
    m_pFrontVec3Control->blockSignals(true);
    m_pFrontVec3Control->setValue(vec);
    m_pFrontVec3Control->blockSignals(false);
}

void LightBaseWidget::onProjMatrixAngleChanged(float angle)
{
    m_pPerspAngleControl->blockSignals(true);
    m_pPerspAngleControl->setCurrentValue(angle);
    m_pPerspAngleControl->blockSignals(false);
}

void LightBaseWidget::onCameraPostionControlValueChanged(const QVector3D& vec)
{
    m_pRenderWidget->setCameraPostion(vec);
}

void LightBaseWidget::onCameraFrontControlValueChanged(const QVector3D& vec)
{
    m_pRenderWidget->setCameraFront(vec);
}

void LightBaseWidget::onProjMatrixAngleControlValueChanged(qreal value, bool cmd)
{
    m_pRenderWidget->setProjMatrixAngle(value);
}

