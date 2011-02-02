/*
 * Qt-based INDI wire protocol client
 * 
 * Copyright (C) 2011 Bogdan Marinov
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include "IndiLightPropertyWidget.hpp"

IndiLightPropertyWidget::IndiLightPropertyWidget(LightProperty* property,
                                                 const QString& title,
                                                 QWidget* parent)
	: IndiPropertyWidget(title, parent)
{
	Q_ASSERT(property);

	setGroup(property->getGroup());

	mainLayout = new QHBoxLayout();
	mainLayout->setContentsMargins(0, 0, 0, 0);
	mainLayout->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);

	//State
	stateWidget = new IndiStateWidget(property->getCurrentState());
	mainLayout->addWidget(stateWidget);

	gridLayout = new QGridLayout();
	gridLayout->setContentsMargins(0, 0, 0, 0);
	QStringList elementNames = property->getElementNames();
	int row = 0;
	foreach (const QString& elementName, elementNames)
	{
		LightElement* element = property->getElement(elementName);

		IndiStateWidget* stateWidget = new IndiStateWidget(element->getValue());
		lightsWidgets.insert(elementName, stateWidget);
		gridLayout->addWidget(stateWidget, row, 0, 1, 1);

		//Labels are immutable and die with the widget
		QLabel* label = new QLabel(element->getLabel());
		label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
		label->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
		gridLayout->addWidget(label, row, 1, 1, 1);

		row++;
	}

	this->setLayout(mainLayout);
}

IndiLightPropertyWidget::~IndiLightPropertyWidget()
{
	//
}

void IndiLightPropertyWidget::updateProperty(Property* property)
{
	Q_UNUSED(property);
}
