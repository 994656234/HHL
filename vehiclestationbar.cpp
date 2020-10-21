#include "vehiclestationbar.h"
#include "ui_vehiclestationbar.h"
#include "qdebug.h"

VehicleStationBar::VehicleStationBar(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::VehicleStationBar)
{
    ui->setupUi(this);
    m_StationIDHash.insert(1,"西二环路");
    m_StationIDHash.insert(2,"孔家营");
    m_StationIDHash.insert(3,"西二环路");
    m_StationIDHash.insert(4,"孔家营");
    m_StationIDHash.insert(5,"西二环路");
    m_StationIDHash.insert(6,"西二环路");
    m_StationIDHash.insert(7,"西二环路");
    m_StationIDHash.insert(8,"西二环路");
    m_StationIDHash.insert(9,"呼钢东路");
    m_StationIDHash.insert(10,"西龙王庙");
    m_StationIDHash.insert(11,"乌兰夫纪念馆");
    m_StationIDHash.insert(12,"呼钢东路");
    m_StationIDHash.insert(13,"西龙王庙");
    m_StationIDHash.insert(14,"西龙王庙");
    m_StationIDHash.insert(15,"乌兰夫纪念馆");
    m_StationIDHash.insert(16,"附属医院");
    m_StationIDHash.insert(17,"新华广场");
    m_StationIDHash.insert(18,"新华广场");
    m_StationIDHash.insert(19,"新华广场");
    m_StationIDHash.insert(20,"博物馆");
    m_StationIDHash.insert(21,"附属医院");
    m_StationIDHash.insert(22,"新华广场");
    m_StationIDHash.insert(23,"新华广场");
    m_StationIDHash.insert(24,"新华广场");
    m_StationIDHash.insert(25,"博物馆");
    m_StationIDHash.insert(26,"将军衙署");
    m_StationIDHash.insert(27,"艺术学院");
    m_StationIDHash.insert(28,"艺术学院");
    m_StationIDHash.insert(29,"东影路");
    m_StationIDHash.insert(30,"将军衙署");
    m_StationIDHash.insert(31,"艺术学院");
    m_StationIDHash.insert(32,"东影路");
    m_StationIDHash.insert(33,"内蒙古展览馆");
    m_StationIDHash.insert(34,"乌兰恰特");
    m_StationIDHash.insert(35,"乌兰恰特");
    m_StationIDHash.insert(36,"乌兰恰特");
    m_StationIDHash.insert(37,"市政府");
    m_StationIDHash.insert(38,"内蒙古展览馆");
    m_StationIDHash.insert(39,"乌兰恰特");
    m_StationIDHash.insert(40,"乌兰恰特");
    m_StationIDHash.insert(41,"乌兰恰特");
    m_StationIDHash.insert(42,"市政府");
    m_StationIDHash.insert(43,"呼和浩特东站");
    m_StationIDHash.insert(44,"后不塔气");
    m_StationIDHash.insert(45,"后不塔气");
    m_StationIDHash.insert(46,"后不塔气");
    m_StationIDHash.insert(47,"什兰岱村");
    m_StationIDHash.insert(48,"呼和浩特东站");
    m_StationIDHash.insert(49,"后不塔气");
    m_StationIDHash.insert(50,"后不塔气");
    m_StationIDHash.insert(51,"后不塔气");
    m_StationIDHash.insert(52,"什兰岱村");
    m_StationIDHash.insert(53,"白塔西");
    m_StationIDHash.insert(54,"坝堰村");
    m_StationIDHash.insert(55,"坝堰村");
    m_StationIDHash.insert(56,"坝堰村");
    m_StationIDHash.insert(57,"坝堰村");
    m_StationIDHash.insert(58,"白塔西");
    m_StationIDHash.insert(59,"坝堰村");
    m_StationIDHash.insert(60,"坝堰村");
    m_StationIDHash.insert(61,"坝堰村");

}

VehicleStationBar::~VehicleStationBar()
{
    delete ui;
}

void VehicleStationBar::updatePage()
{
    //站点信息
//    if(1)
//    {
//        ui->lbl_currentStationValue->setText(m_StationIDHash[database->CTHM_CurrentStation_U32]);
//    }
//    else
//    {
//        ui->lbl_currentStationValue->setText("--");
//    }

//    if(database->CTHM_NextStationID_U32>0&&database->CTHM_NextStationID_U32<62)
//    {
//        ui->lbl_nextStationValue->setText(m_StationIDHash[database->CTHM_NextStationID_U32]);
//    }
//    else
//    {
//        ui->lbl_nextStationValue->setText("--");
//    }

//    if(database->CTHM_LastStationID_U32>0&&database->CTHM_LastStationID_U32<62)
//    {
//        ui->lbl_terminalStationValue->setText(m_StationIDHash[database->CTHM_LastStationID_U32]);
//    }
//    else
//    {
//        ui->lbl_terminalStationValue->setText("--");
//    }

    //网压
    ui->lbl_networkVoltageValue->setText(QString::number((int)(database->CTD_CatenaryVoltage_U16)));
    ui->lbl_batteryVoltageValue->setText(QString::number(qMax(database->ACU1CT_IuiBtyVltg_U16,database->ACU2CT_IuiBtyVltg_U16)));


}
