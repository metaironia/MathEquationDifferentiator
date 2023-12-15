#ifndef LATEX_ROFLS_H
#define LATEX_ROFLS_H

const char *LATEX_SIMPLIFY_QUOTATIONS[] = {

    "Изи сократим:\n",
    "Сократим выражения с локтя:\n",
    "С помощью магии получим:\n",
    "Мне похуй, я так чувствую:\n"
};

const int LATEX_SIMPLIFY_QUOTATION_NUMBER = sizeof (LATEX_SIMPLIFY_QUOTATIONS) /
                                                                    sizeof (LATEX_SIMPLIFY_QUOTATIONS[0]);

const char *LATEX_SERIOUS_QUOTATIONS[] = {

    "Имеем данное выражение:\n",
    "Итак, имеем:\n",
    "Давайте поработаем с\n",
    "Что это за дерьмо ниже?\n"
};

const int LATEX_SERIOUS_QUOTATION_NUMBER = sizeof (LATEX_SERIOUS_QUOTATIONS) /
                                                                    sizeof (LATEX_SERIOUS_QUOTATIONS[0]);

const char *LATEX_DERIVATIVE_QUOTATIONS[] = {

    "Производная этой херни:\n",
    "Возьмем derivative этого.\n",
    "Попробуем хлопнуть в ладоши.\n",
    "Компьютер сейчас выключится!!!\n"
};

const int LATEX_DERIVATIVE_QUOTATION_NUMBER = sizeof (LATEX_DERIVATIVE_QUOTATIONS) /
                                                                    sizeof (LATEX_DERIVATIVE_QUOTATIONS[0]);


#endif
