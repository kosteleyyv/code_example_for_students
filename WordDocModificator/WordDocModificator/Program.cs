using Microsoft.Office.Interop.Word;
using System;

namespace WordDocModificator
{
    class Program
    {
        static uint _sectionNumber = 0;
        static uint _pictureNumber = 0;
        static uint _tableNumber = 0;

        static void Main(string[] args)
        {
            string sourcePath = @"E:\студенты\СПРБП\шаблон rtf.rtf";
            string distPath = @"E:\студенты\СПРБП\result.rtf";
            string csvPath = "";

            var application = new Application();
            application.Visible = true;

            var document = application.Documents.Open(sourcePath);

            string[] templateStringList =
                {
                "[*имя раздела*]",///0
                "[*имя рисунка*]",///1
                "[*ссылка на следующий рисунок*]",///2
                "[*ссылка на предыдущий рисунок*]",///3
                "[*ссылка на таблицу*]",///4
                "[*таблица первая*]"///5
                };


            Paragraph prevParagraph = null;

            foreach (Paragraph paragraph in document.Paragraphs)
            {
                for (int i = 0; i < templateStringList.Length; i++)
                {
                    if (paragraph.Range.Text.Contains(templateStringList[i]))
                    {
                        switch (i)
                        {
                            case 0:
                                {
                                    _sectionNumber++;

                                    paragraph.Alignment = WdParagraphAlignment.wdAlignParagraphCenter;
                                    paragraph.Range.Font.Name = "Times New Roman";
                                    paragraph.Range.Font.Size = 15;
                                    paragraph.Format.SpaceAfter = 12;
                                    paragraph.Range.Font.Bold = 1;
                                    paragraph.Range.HighlightColorIndex = 0;

                                    Object missing = System.Type.Missing;
                                    string replaceString = _sectionNumber.ToString();

                                    paragraph.Range.Find.Execute(templateStringList[i],
                                   ref missing, ref missing, ref missing, ref missing, ref missing, ref missing,
                                    0, ref missing, replaceString, 2, ref missing, ref missing,
                                   ref missing, ref missing);
                                }
                                break;
                            case 1:
                                {
                                    _pictureNumber++;

                                    paragraph.Alignment = WdParagraphAlignment.wdAlignParagraphCenter;
                                    paragraph.Range.Font.Name = "Times New Roman";
                                    paragraph.Range.Font.Size = 12;
                                    paragraph.Format.SpaceAfter = 12;
                                    paragraph.Range.HighlightColorIndex = 0;

                                    if (prevParagraph != null)
                                    {
                                        prevParagraph.Format.SpaceBefore = 12;
                                    }

                                    Object missing = System.Type.Missing;
                                    string replaceString = "Рисунок " + _sectionNumber.ToString() + "." + _pictureNumber.ToString() + " -";
                                    paragraph.Range.Find.Execute(templateStringList[i],
                                   ref missing, ref missing, ref missing, ref missing, ref missing, ref missing,
                                    0, ref missing, replaceString, 2, ref missing, ref missing,
                                   ref missing, ref missing);
                                    //  paragraph.Range.Text = paragraph.Range.Text.Replace(templateStringList[i],
                                    //    );
                                }
                                break;
                            case 2:
                                {
                                    Object missing = System.Type.Missing;
                                    string replaceString = _sectionNumber.ToString() + "." + (_pictureNumber + 1).ToString();
                                    paragraph.Range.Find.Execute(templateStringList[i],
                                   ref missing, ref missing, ref missing, ref missing, ref missing, ref missing,
                                    0, ref missing, replaceString, 2, ref missing, ref missing,
                                   ref missing, ref missing);
                                }
                                break;
                            case 3:
                                {
                                    Object missing = System.Type.Missing;
                                    string replaceString = _sectionNumber.ToString() + "." + _pictureNumber.ToString();
                                    paragraph.Range.Find.Execute(templateStringList[i],
                                   ref missing, ref missing, ref missing, ref missing, ref missing, ref missing,
                                    0, ref missing, replaceString, 2, ref missing, ref missing,
                                   ref missing, ref missing);
                                }
                                break;
                            case 4:
                                {
                                    _tableNumber++;

                                    Object missing = System.Type.Missing;
                                    string replaceString = _sectionNumber.ToString() + "." + _tableNumber.ToString();
                                    paragraph.Range.Find.Execute(templateStringList[i],
                                   ref missing, ref missing, ref missing, ref missing, ref missing, ref missing,
                                    0, ref missing, replaceString, 2, ref missing, ref missing,
                                   ref missing, ref missing);
                                }
                                break;
                            case 5:
                                {

                                }
                                break;

                        }
                    }
                }

                prevParagraph = paragraph;

            }
            document.SaveAs2(distPath);

            // Close word.
            // application.Quit();
        }
    }
}
