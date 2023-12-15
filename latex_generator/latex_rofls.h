#ifndef LATEX_ROFLS_H
#define LATEX_ROFLS_H

const char *LATEX_SIMPLIFY_QUOTATIONS[] = {

    "��� ��������:\n",
    "�������� ��������� � �����:\n",
    "� ������� ����� �������:\n",
    "��� �����, � ��� ��������:\n"
};

const int LATEX_SIMPLIFY_QUOTATION_NUMBER = sizeof (LATEX_SIMPLIFY_QUOTATIONS) /
                                                                    sizeof (LATEX_SIMPLIFY_QUOTATIONS[0]);

const char *LATEX_SERIOUS_QUOTATIONS[] = {

    "����� ������ ���������:\n",
    "����, �����:\n",
    "������� ���������� �\n",
    "��� ��� �� ������ ����?\n"
};

const int LATEX_SERIOUS_QUOTATION_NUMBER = sizeof (LATEX_SERIOUS_QUOTATIONS) /
                                                                    sizeof (LATEX_SERIOUS_QUOTATIONS[0]);

const char *LATEX_DERIVATIVE_QUOTATIONS[] = {

    "����������� ���� �����:\n",
    "������� derivative �����.\n",
    "��������� �������� � ������.\n",
    "��������� ������ ����������!!!\n"
};

const int LATEX_DERIVATIVE_QUOTATION_NUMBER = sizeof (LATEX_DERIVATIVE_QUOTATIONS) /
                                                                    sizeof (LATEX_DERIVATIVE_QUOTATIONS[0]);


#endif
