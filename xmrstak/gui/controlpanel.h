#pragma once

#include <QFrame>
#include <QWidget>
#include <QPushButton>
#include <QGraphicsDropShadowEffect>


class ControlPanel : public QWidget {
	Q_OBJECT

	public:
		explicit ControlPanel(QWidget* parent = 0);
		virtual ~ControlPanel();

	private:
		QPalette* _backgroundColor = nullptr;

		QGraphicsDropShadowEffect* _big_button_shadow = nullptr;
		QGraphicsDropShadowEffect* _medium_button_shadow = nullptr;
		QGraphicsDropShadowEffect* _small_button_shadow = nullptr;

		// Left button panel
		QFrame* _main_L_Frame = nullptr;
		QFrame* _sec_T_LFrame = nullptr;
		QFrame* _sec_C_LFrame = nullptr;
		QFrame* _sec_B_LFrame = nullptr;

		QPushButton* _console_button = nullptr;
		QPushButton* _config_button = nullptr;

		QGraphicsDropShadowEffect* _console_shadow = nullptr;
		QGraphicsDropShadowEffect* _config_shadow = nullptr;
		//---

		// Center button panel
		QFrame* _main_C_Frame = nullptr;
		QFrame* _sec_T_CFrame = nullptr;
		QFrame* _sec_C_CFrame = nullptr;
		QFrame* _sec_B_CFrame = nullptr;

		QPushButton* _play_button = nullptr;
		QGraphicsDropShadowEffect* _play_shadow = nullptr;
		//---

		// Right button panel
		QFrame* _main_R_Frame = nullptr;
		QFrame* _sec_T_RFrame = nullptr;
		QFrame* _sec_C_RFrame = nullptr;
		QFrame* _sec_B_RFrame = nullptr;

		QPushButton* _stats_button = nullptr;
		QPushButton* _result_button = nullptr;
		QGraphicsDropShadowEffect* _stats_shadow = nullptr;
		QGraphicsDropShadowEffect* _result_shadow = nullptr;
		//---

		// windows system buttons panel
		QFrame* _win_L_CFrame = nullptr;
		QFrame* _win_R_RFrame = nullptr;

		QPushButton* _win_minimize_button = nullptr;
		QPushButton* _win_maximize_button = nullptr;
		QPushButton* _win_close_button = nullptr;
		//---
};