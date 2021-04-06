#include "vehiclestationbar.h"
#include "ui_vehiclestationbar.h"
#include "qdebug.h"

VehicleStationBar::VehicleStationBar(QWidget *parent) :
    MyBase(parent),
    ui(new Ui::VehicleStationBar)
{
    ui->setupUi(this);
    m_StationIDHash.insert(4098,"余杭高铁站");
    m_StationIDHash.insert(4097,"余杭高铁站");
    m_StationIDHash.insert(4100,"余杭高铁站");
    m_StationIDHash.insert(4099,"余杭高铁站");
    m_StationIDHash.insert(4354,"许村站");
    m_StationIDHash.insert(4356,"许村站");
    m_StationIDHash.insert(4353,"许村站");
    m_StationIDHash.insert(4610,"海宁高铁西站");
    m_StationIDHash.insert(4611,"海宁高铁西站");
    m_StationIDHash.insert(4612,"海宁高铁西站");
    m_StationIDHash.insert(4609,"海宁高铁西站");
    m_StationIDHash.insert(4614,"海宁高铁西站");
    m_StationIDHash.insert(4866,"长安站");
    m_StationIDHash.insert(4865,"长安站");
    m_StationIDHash.insert(4867,"长安站");
    m_StationIDHash.insert(8450,"长安东站");
    m_StationIDHash.insert(8449,"长安东站");
    m_StationIDHash.insert(8707,"周王庙站");
    m_StationIDHash.insert(8706,"周王庙站");
    m_StationIDHash.insert(8705,"周王庙站");
    m_StationIDHash.insert(8194,"盐官站");
    m_StationIDHash.insert(8193,"盐官站");
    m_StationIDHash.insert(8196,"盐官站");
    m_StationIDHash.insert(8198,"盐官站");
    m_StationIDHash.insert(8195,"盐官站");
    m_StationIDHash.insert(8197,"盐官站");
    m_StationIDHash.insert(8199,"盐官站");
    m_StationIDHash.insert(8201,"盐官站");
    m_StationIDHash.insert(8203,"盐官站");
    m_StationIDHash.insert(12546,"桐九公路站");
    m_StationIDHash.insert(12545,"桐九公路站");
    m_StationIDHash.insert(12803,"斜桥站");
    m_StationIDHash.insert(12802,"斜桥站");
    m_StationIDHash.insert(12801,"斜桥站");
    m_StationIDHash.insert(13059,"皮革城站");
    m_StationIDHash.insert(13058,"皮革城站");
    m_StationIDHash.insert(13057,"皮革城站");
    m_StationIDHash.insert(13314,"海昌路站");
    m_StationIDHash.insert(13313,"海昌路站");
    m_StationIDHash.insert(12290,"浙大国际学院站");
    m_StationIDHash.insert(12292,"浙大国际学院站");
    m_StationIDHash.insert(12289,"浙大国际学院站");
    m_StationIDHash.insert(12291,"浙大国际学院站");

    m_StationID.insert(1,"余杭高铁站");
    m_StationID.insert(2,"许村站");
    m_StationID.insert(3,"海宁高铁西站");
    m_StationID.insert(4,"长安站");
    m_StationID.insert(5,"长安东站");
    m_StationID.insert(6,"周王庙站");
    m_StationID.insert(7,"盐官站");
    m_StationID.insert(8,"桐九公路站");
    m_StationID.insert(9,"斜桥站");
    m_StationID.insert(10,"皮革城站");
    m_StationID.insert(11,"海昌路站");
    m_StationID.insert(12,"浙大国际学院站");

}

VehicleStationBar::~VehicleStationBar()
{
    delete ui;
}

void VehicleStationBar::updatePage()
{
    if(database->CTD_HALFSTATUS_B1 == true)
    {
        SetSemiAutoStation();
    }
    else
    {
        SetAutoStation();
    }

    //网压
    ui->lbl_networkVoltageValue->setText(QString::number((int)(database->CTD_CatenaryVoltage_U16)));
    ui->lbl_batteryVoltageValue->setText(QString::number(qMax(database->ACU1CT_IuiBtyVltg_U16,database->ACU2CT_IuiBtyVltg_U16)));

}

void VehicleStationBar::SetAutoStation()
{
    bool nextstationflg = false;
    QString nextstationstr = "";

//    database->ATCiCT_A6_B1 = true;
//    database->ATCiCT_A14_U32 = 4098;
//    database->ATCiCT_A5_B1 = true;
//    database->ATCiCT_A13_U32 = 12291;

    if(database->ATCiCT_A6_B1 == true)
    {
        QHash<unsigned int, QString>::iterator i = m_StationIDHash.find(database->ATCiCT_A14_U32);

        while (i != m_StationIDHash.end())
        {
            if (i.key() == database->ATCiCT_A14_U32)
            {
                nextstationflg = true;
                nextstationstr = m_StationIDHash[i.key()];
                break;
            }
            nextstationflg = false;
        }
        if (nextstationflg == true)
        {
            for (int key= 1; key <= m_StationID.size(); key++)
            {
                if (m_StationID[key] == nextstationstr)
                {
                    if ("余杭高铁站" == m_StationIDHash[database->ATCiCT_A13_U32]) //上行
                    {
                        if (key < 12)
                        {
                            ui->lbl_currentStationValue->setText(m_StationID[key+1]);
                        }
                        else
                        {
                            ui->lbl_currentStationValue->setText(m_StationID[12]);
                        }
                        break;
                    }
                    else if ("浙大国际学院站" == m_StationIDHash[database->ATCiCT_A13_U32])
                    {
                        if (key > 1)
                        {
                            ui->lbl_currentStationValue->setText(m_StationID[key-1]);
                        }
                        else
                        {
                            ui->lbl_currentStationValue->setText(m_StationID[1]);
                        }
                        break;
                    }
                    else
                    {
                        ui->lbl_currentStationValue->setText("--");
                    }
                }
//                else
//                {
//                    ui->lbl_currentStationValue->setText("--");
//                }
            }

            ui->lbl_nextStationValue->setText(m_StationIDHash[database->ATCiCT_A14_U32]);
        }
    }
    else
    {
        ui->lbl_nextStationValue->setText("--");
        ui->lbl_currentStationValue->setText("--");
    }

    if(database->ATCiCT_A5_B1 == true)
    {
        ui->lbl_terminalStationValue->setText(m_StationIDHash[database->ATCiCT_A13_U32]);
    }
    else
    {
        ui->lbl_terminalStationValue->setText("--");
    }

}

void VehicleStationBar::SetSemiAutoStation()
{
    if (database->CTD_CurrentStatiOLINE_U32 > 0 && database->CTD_CurrentStatiOLINE_U32<= 12)
    {
        ui->lbl_currentStationValue->setText(m_StationID[database->CTD_CurrentStatiOLINE_U32]);
    }
    else
    {
        ui->lbl_currentStationValue->setText("--");
    }

    if (database->CTD_NextStatiOLINEID_U32 > 0 && database->CTD_NextStatiOLINEID_U32<= 12)
    {
        ui->lbl_nextStationValue->setText(m_StationID[database->CTD_NextStatiOLINEID_U32]);
    }
    else
    {
        ui->lbl_nextStationValue->setText("--");
    }
    if (database->CTD_LastStatiOLINEID_U32 > 0 && database->CTD_LastStatiOLINEID_U32<= 12)
    {
        ui->lbl_terminalStationValue->setText(m_StationID[database->CTD_LastStatiOLINEID_U32]);
    }
    else
    {
        ui->lbl_terminalStationValue->setText("--");
    }
}
