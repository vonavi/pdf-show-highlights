/*
 * Copyright (C) 2013 Vladimir S. Ivanov
 *
 * Author: Vladimir S. Ivanov <ivvl82@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <poppler/glib/poppler.h>

int main (int argc, char *argv[]) {

    /* argc should be 2 for correct execution */
    if (argc != 2)
        g_printf ("Usage: %s filename\n", argv[0]);
    else {

#if !(GLIB_CHECK_VERSION(2,36,0))
        g_type_init ();
#endif

        gchar *filename, *uri;
        filename = realpath (argv[1], NULL);
        uri = g_filename_to_uri (filename, NULL, NULL);

        PopplerDocument *document;
        document = poppler_document_new_from_file (uri, NULL, NULL);

        g_free (filename); g_free (uri);

        /* Returns the NULL pointer on failure */
        if (document == NULL)
            g_printf ("Could not open file\n");
        else {
            int n_pages, index;
            n_pages = poppler_document_get_n_pages (document);

            for (index=0; index<n_pages; ++index) {
                PopplerPage *page;
                GList *list, *l;
                page = poppler_document_get_page (document, index);
                list = poppler_page_get_annot_mapping (page);

                for (l = list; l; l = g_list_next (l)) {
                    PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)l->data;
                    PopplerAnnot *annot = (PopplerAnnot *)mapping->annot;

                    /* Show highlight annotations only */
                    PopplerAnnotType type = poppler_annot_get_annot_type (annot);
                    if (type == POPPLER_ANNOT_HIGHLIGHT) {

                        /* Invert the y coords before calling
                         * poppler_page_get_selected_text() */
                        PopplerRectangle selection = mapping->area, pdf_selection;
                        double height;
                        poppler_page_get_size (page, NULL, &height);
                        pdf_selection.x1 = selection.x1;
                        pdf_selection.y1 = height - selection.y1;
                        pdf_selection.x2 = selection.x2;
                        pdf_selection.y2 = height - selection.y2;

                        gchar *text;
                        text = poppler_page_get_selected_text
                            (page, POPPLER_SELECTION_WORD, &pdf_selection);
                        g_printf ("\"%s\" (p. %d)\n\n", text, index+1);
                        g_free (text);

                        poppler_rectangle_free (&selection);
                        poppler_rectangle_free (&pdf_selection);
                    }
               }

                poppler_page_free_annot_mapping (list);
                poppler_page_free_annot_mapping (l);
                g_object_unref (G_OBJECT (page));
            }

            g_object_unref (G_OBJECT (document));
        }
    }
}
