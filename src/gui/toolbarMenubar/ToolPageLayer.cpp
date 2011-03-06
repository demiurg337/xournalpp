#include "ToolPageLayer.h"
#include <config.h>
#include <glib/gi18n-lib.h>

ToolPageLayer::ToolPageLayer(ActionHandler * handler, String id, ActionType type) :
	AbstractToolItem(id, handler, type, NULL) {
	layerComboBox = gtk_combo_box_new_text();
	layerCount = -5;
	inCbUpdate = false;

	g_signal_connect(layerComboBox, "changed", G_CALLBACK(&cbSelectCallback), this);
}

ToolPageLayer::~ToolPageLayer() {
}

void ToolPageLayer::cbSelectCallback(GtkComboBox * widget, ToolPageLayer * tpl) {
	if (tpl->inCbUpdate) {
		return;
	}

	GtkComboBox * cb = GTK_COMBO_BOX(tpl->layerComboBox);
	int count = gtk_tree_model_iter_n_children(gtk_combo_box_get_model(cb), NULL);
	int selected = count - gtk_combo_box_get_active(widget) - 1;

	tpl->handler->actionPerformed(ACTION_FOOTER_LAYER, GROUP_NOGROUP, NULL, NULL, NULL, true);
}

int ToolPageLayer::getSelectedLayer() {
	GtkComboBox * cb = GTK_COMBO_BOX(layerComboBox);
	int count = gtk_tree_model_iter_n_children(gtk_combo_box_get_model(cb), NULL);
	int selected = count - gtk_combo_box_get_active(cb) - 1;
	return selected;
}

void ToolPageLayer::setSelectedLayer(int selected) {
	GtkComboBox * cb = GTK_COMBO_BOX(layerComboBox);
	int count = gtk_tree_model_iter_n_children(gtk_combo_box_get_model(cb), NULL);

	gtk_combo_box_set_active(cb, count - selected - 1);
}

void ToolPageLayer::setLayerCount(int layer, int selected) {
	inCbUpdate = true;

	int count = gtk_tree_model_iter_n_children(gtk_combo_box_get_model(GTK_COMBO_BOX(layerComboBox)), NULL);

	for (int i = count - 1; i >= 0; i--) {
		gtk_combo_box_remove_text(GTK_COMBO_BOX(layerComboBox), i);
	}

	gtk_combo_box_append_text(GTK_COMBO_BOX(layerComboBox), "Background");
	for (int i = 1; i <= layer; i++) {
		char * text = g_strdup_printf(_("Layer %i"), i);
		gtk_combo_box_prepend_text(GTK_COMBO_BOX(layerComboBox), text);
		g_free(text);
	}

	setSelectedLayer(selected);

	this->layerCount = layer;
	inCbUpdate = false;
}

GtkToolItem * ToolPageLayer::newItem() {
	GtkToolItem * it = gtk_tool_item_new();

	GtkWidget * hbox = gtk_hbox_new(false, 1);
	gtk_box_pack_start(GTK_BOX(hbox), gtk_label_new(_("Layer")), false, false, 7);

	gtk_box_pack_start(GTK_BOX(hbox), layerComboBox, false, false, 0);

	gtk_container_add(GTK_CONTAINER(it), hbox);

	return it;
}

