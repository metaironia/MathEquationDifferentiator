#include <assert.h>
#include <stdio.h>

#include "latex_generator.h"


LatexFuncStatus LatexBegin (FILE* latex_file) {

    assert (latex_file);

    fprintf (latex_file,    "\\documentclass[a4paper,12pt]{article}\n"
                            "\\usepackage{cmap}\n"
                            "\\usepackage{mathtext}\n"
                            "\\usepackage[T2A]{fontenc}\n"
                            "\\usepackage[utf8]{inputenc}\n"
                            "\\usepackage[english,russian]{babel}\n"
                            "\\usepackage{amsmath,amsfonts,amssymb,amsthm,mathtools}\n"
                            "\\usepackage{icomma}\n"

                            "\\DeclareMathOperator{\\sgn}{\\mathop{sgn}}\n"
                            "\\newcommand*{\\hm}[1]{#1\\nobreak\\discretionary{}\n"
                            "{\\hbox{$\\mathsurround=0pt #1$}}{}}\n"

                            "\\usepackage{graphicx}\n"
                            "\\graphicspath{{images/}{images2/}}\n"
                            "\\usepackage{wrapfig}\n"

                            "\\usepackage{array,tabularx,tabulary,booktabs}\n"
                            "\\usepackage{longtable}\n"
                            "\\usepackage{multirow}\n"

                            "\\theoremstyle{plain}\n"
                            "\\newtheorem{theorem}{Теорема}[section]\n"
                            "\\newtheorem{proposition}[theorem]{Утверждение}\n"

                            "\\theoremstyle{definition}\n"
                            "\\newtheorem{corollary}{Следствие}[theorem]\n"
                            "\\newtheorem{problem}{Задача}[section]\n"

                            "\\theoremstyle{remark}\n"
                            "\\newtheorem*{nonum}{Решение}\n"

                            "\\usepackage{etoolbox}\n"

                            "\\usepackage{extsizes}\n"
                            "\\usepackage{geometry}\n"
                            "	\\geometry{top=25mm}\n"
                            "	\\geometry{bottom=35mm}\n"
                            "	\\geometry{left=20mm}\n"
                            "	\\geometry{right=20mm}\n"

                            "\\usepackage{setspace}\n"

                            "\\usepackage{lastpage}\n"

                            "\\usepackage{soul}\n"

                            "\\usepackage{hyperref}\n"
                            "\\usepackage[usenames,dvipsnames,svgnames,table,rgb]{xcolor}\n"
                            "\\hypersetup{\n"
                            "    unicode=true,\n"
                            "    pdftitle={Заголовок},\n"
                            "    pdfauthor={Автор},\n"
                            "    pdfsubject={Тема},\n"
                            "    pdfcreator={Создатель},\n"
                            "    pdfproducer={Производитель},\n"
                            "    pdfkeywords={keyword1} {key2} {key3},\n"
                            "    colorlinks=true,\n"
                            "    linkcolor=black,\n"
                            "    citecolor=black,\n"
                            "    filecolor=magenta,\n"
                            "    urlcolor=cyan\n"
                            "}\n"

                            "\\usepackage{csquotes}\n"

                            "\\usepackage{multicol}\n"

                            "\\usepackage{tikz}\n"
                            "\\usetikzlibrary{calc}\n"
                            "\\usepackage{tkz-euclide}\n"
                            "\\usepackage{pgfplots}\n"
                            "\\pgfplotsset{compat=1.18}\n"
                            "\\usetikzlibrary{pgfplots.polar}\n"
                            "\\usepackage{pgfplotstable}\n"

                            "\\author{Кулагин Сергей}\n"
                            "\\title{Главная дерьмина в моей жизни в \\LaTeX}\n"
                            "\\date{\\today}\n"

                            "\\begin{document}\n");

    return LATEX_FUNC_STATUS_OK;
}

LatexFuncStatus LatexEnd (FILE *latex_file) {

    assert (latex_file);

    fprintf (latex_file,    "\\begin{thebibliography}{}\n"
                            "\\bibitem{Arithmetica} Margin of a copy of Arithmetica --- Diophantus of Alexandria, Pierre de Fermat\n"
                            "\\bibitem{Universe} Kak upravlat Vselennoi, ne privlekaya vnimaniya sanitarov --- Artem Bester\n"
                            "\\bibitem{Ruses} History of ancient Ruses - professor Bagirov\n"

                            "\\end{thebibliography}\n"

                            "\\end{document}\n");

    return LATEX_FUNC_STATUS_OK;
}


