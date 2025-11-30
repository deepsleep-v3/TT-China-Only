using Spectre.Console;
using System;
using System.Collections.Generic;
using System.Globalization;
using System.Threading;

namespace TT
{
    public class PublicVariables
    {
        public static Dictionary<string, Dictionary<string, string>> i18nStringsTable;
        public static string selectedCulture = "en-US";
    }
    class EasyPractice : PracticeGenerator
    {
        public EasyPractice() : base()
        {
            charCount = 21;
        }

        public override void Invoke()
        {
            string randomString = RandomStringConstructor();
            while (true)
            {
                var start = DateTime.Now;
                Console.WriteLine(string.Format(PublicVariables.i18nStringsTable[PublicVariables.selectedCulture]["generated_msg"], randomString));
                string repeat = Console.ReadLine() ?? "";
                if (repeat == randomString)
                {
                    var PCTT =
                        ((DateTime.Now - start).Days * 24 * 60 * 60 + (DateTime.Now - start).Hours * 60 * 60 +
                        (DateTime.Now - start).Minutes * 60 + (DateTime.Now - start).TotalSeconds) / charCount;
                    Console.WriteLine(string.Format(PublicVariables.i18nStringsTable[PublicVariables.selectedCulture]["challenge_successfully"], charCount));
                    Console.WriteLine("Total: " +
                        (DateTime.Now - start).ToString("g", new CultureInfo(PublicVariables.selectedCulture)) +
                        ", Per Character Time Taken (in seconds): " + PCTT);
                    break;
                }
                else
                {
                    Console.WriteLine(PublicVariables.i18nStringsTable[PublicVariables.selectedCulture]["incorrect"]);
                    Console.Clear();
                    continue;
                }
            }
        }
    }
    class MiddlePractice : PracticeGenerator
    {
        public MiddlePractice() : base()
        {
            charCount = 62;
        }

        public override void Invoke()
        {
            string randomString = RandomStringConstructor();
            while (true)
            {
                var start = DateTime.Now;
                Console.WriteLine(string.Format(PublicVariables.i18nStringsTable[PublicVariables.selectedCulture]["generated_msg"], randomString));
                string repeat = Console.ReadLine() ?? "";
                if (repeat == randomString)
                {
                    var PCTT =
                        ((DateTime.Now - start).Days * 24 * 60 * 60 + (DateTime.Now - start).Hours * 60 * 60 +
                        (DateTime.Now - start).Minutes * 60 + (DateTime.Now - start).TotalSeconds) / charCount;
                    Console.WriteLine(string.Format(PublicVariables.i18nStringsTable[PublicVariables.selectedCulture]["challenge_successfully"], charCount));
                    Console.WriteLine("Total: " +
                        (DateTime.Now - start).ToString("g", new CultureInfo(PublicVariables.selectedCulture)) +
                        ", Per Character Time Taken (in seconds): " + PCTT);
                    break;
                }
                else
                {
                    Console.WriteLine(PublicVariables.i18nStringsTable[PublicVariables.selectedCulture]["incorrect"]);
                    Console.Clear();
                    continue;
                }
            }
        }
    }
    class HardPractice : PracticeGenerator
    {
        public HardPractice() : base()
        {
            charCount = 100;
        }

        public override void Invoke()
        {
            string randomString = RandomStringConstructor();
            while (true)
            {
                var start = DateTime.Now;
                Console.WriteLine(string.Format(PublicVariables.i18nStringsTable[PublicVariables.selectedCulture]["generated_msg"], randomString));
                string repeat = Console.ReadLine() ?? "";
                if (repeat == randomString)
                {
                    var PCTT =
                        ((DateTime.Now - start).Days * 24 * 60 * 60 + (DateTime.Now - start).Hours * 60 * 60 +
                        (DateTime.Now - start).Minutes * 60 + (DateTime.Now - start).TotalSeconds) / charCount;
                    Console.WriteLine(string.Format(PublicVariables.i18nStringsTable[PublicVariables.selectedCulture]["challenge_successfully"], charCount));
                    Console.WriteLine("Total: " +
                        (DateTime.Now - start).ToString("g", new CultureInfo(PublicVariables.selectedCulture)) +
                        ", Per Character Time Taken (in seconds): " + PCTT);
                    break;
                }
                else
                {
                    Console.WriteLine(PublicVariables.i18nStringsTable[PublicVariables.selectedCulture]["incorrect"]);
                    Console.Clear();
                    continue;
                }
            }
        }
    }
    class VeryHardPractice : PracticeGenerator
    {
        public VeryHardPractice() : base()
        {
            charCount = 248;
        }

        public override void Invoke()
        {
            string randomString = RandomStringConstructor();
            while (true)
            {
                var start = DateTime.Now;
                Console.WriteLine(string.Format(PublicVariables.i18nStringsTable[PublicVariables.selectedCulture]["generated_msg"], randomString));
                string repeat = Console.ReadLine() ?? "";
                if (repeat == randomString)
                {
                    var PCTT =
                        ((DateTime.Now - start).Days * 24 * 60 * 60 + (DateTime.Now - start).Hours * 60 * 60 +
                        (DateTime.Now - start).Minutes * 60 + (DateTime.Now - start).TotalSeconds) / charCount;
                    Console.WriteLine(string.Format(PublicVariables.i18nStringsTable[PublicVariables.selectedCulture]["challenge_successfully"], charCount));
                    Console.WriteLine("Total: " +
                        (DateTime.Now - start).ToString("g", new CultureInfo(PublicVariables.selectedCulture)) +
                        ", Per Character Time Taken (in seconds): " + PCTT);
                    break;
                }
                else
                {
                    Console.WriteLine(PublicVariables.i18nStringsTable[PublicVariables.selectedCulture]["incorrect"]);
                    Console.Clear();
                    continue;
                }
            }
        }
    }
    abstract class PracticeGenerator
    {
        Random _randomAlg = new();
        protected int charCount = 62;
        protected string _charList = "QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890";
        protected string RandomStringConstructor()
        {
            char[] resultCharSequence = new char[charCount];
            for (int i = 0; i < charCount; i++)
            {
                resultCharSequence[i] = _charList[_randomAlg.Next(62)];
            }
            return new string(resultCharSequence);
        }
        public abstract void Invoke();
    }
    internal class Program
    {
        static void Main(string[] args)
        {
            PublicVariables.i18nStringsTable = new Dictionary<string, Dictionary<string, string>>()
            {
                { "en-US", new Dictionary<string, string>()
                    {
                        { "generated_msg", "Please type the following string: {0}" },
                        { "challenge_successfully", "Congratulations! You have successfully completed the challenge with {0} characters!" },
                        { "incorrect", "Incorrect input. Please try again." },
                        { "select_difficulty", "please select [greenyellow]practice difficulty for you[/]" },
                        { "try_again", "Try Again?" }
                    }
                },
                { "zh-TW", new Dictionary<string, string>()
                    {
                        { "generated_msg", "請輸入以下字串: {0}" },
                        { "challenge_successfully", "恭喜！你已成功完成包含 {0} 個字元的挑戰！" },
                        { "incorrect", "輸入錯誤。請再試一次。" },
                        { "select_difficulty", "請選擇適合你的[greenyellow]練習難度[/]" },
                        { "try_again", "再試一次？" }
                    }
                },
            };
            Console.Clear();

            var choice = AnsiConsole.Prompt(
                new SelectionPrompt<string>()
                    .Title("Select your [greenyellow]language[/] / 選擇你的[greenyellow]語言[/]")
                    .AddChoices(new[] { "English", "繁體中文（臺灣）" })
                    .HighlightStyle("chartreuse1 bold rapidblink")
            );
            switch (choice)
            {
                case "English":
                    PublicVariables.selectedCulture = "en-US";
                    break;
                case "繁體中文（臺灣）":
                    PublicVariables.selectedCulture = "zh-TW";
                    break;
            }
            while (true) {
                Console.Clear();
                PracticeGenerator practice;
                choice = AnsiConsole.Prompt(
                    new SelectionPrompt<string>()
                        .Title(PublicVariables.i18nStringsTable[PublicVariables.selectedCulture]["select_difficulty"])
                        .AddChoices(new[] { "Easy (26 alphabets and number)", "Medium (62 alphabets and number)", "Hard (100 alphabets and number)", "Very Hard (248 alphabets and number)" })
                        .HighlightStyle("chartreuse1 bold rapidblink")
                );
                switch (choice)
                {
                    case "Easy (26 alphabets and number)":
                        practice = new EasyPractice();
                        AnsiConsole.MarkupLine("[bold greenyellow]You will into a easy practice: 3 seconds[/]");
                        Thread.Sleep(1000);
                        Console.Clear();
                        AnsiConsole.MarkupLine("[bold yellow]You will into a easy practice: 2 seconds[/]");
                        Thread.Sleep(1000);
                        Console.Clear();
                        AnsiConsole.MarkupLine("[bold orange1]You will into a easy practice: 1 seconds[/]");
                        Thread.Sleep(1000);
                        Console.Clear();
                        practice.Invoke();
                        break;
                    case "Medium (62 alphabets and number)":
                        practice = new MiddlePractice();
                        AnsiConsole.MarkupLine("[bold greenyellow]You will into a medium practice: 3 seconds[/]");
                        Thread.Sleep(1000);
                        Console.Clear();
                        AnsiConsole.MarkupLine("[bold yellow]You will into a medium practice: 2 seconds[/]");
                        Thread.Sleep(1000);
                        Console.Clear();
                        AnsiConsole.MarkupLine("[bold orange1]You will into a medium practice: 1 seconds!![/]");
                        Thread.Sleep(1000);
                        Console.Clear();
                        practice.Invoke();
                        break;
                    case "Hard (100 alphabets and number)":
                        practice = new HardPractice();
                        AnsiConsole.MarkupLine("[bold greenyellow]You will into a hard practice: 3 seconds[/]");
                        Thread.Sleep(1000);
                        Console.Clear();
                        AnsiConsole.MarkupLine("[bold yellow]You will into a hard practice: 2 seconds[/]");
                        Thread.Sleep(1000);
                        Console.Clear();
                        AnsiConsole.MarkupLine("[bold orange1]You will into a hard practice: 1 seconds!![/]");
                        break;
                    case "Very Hard (248 alphabets and number)":
                        practice = new VeryHardPractice();
                        AnsiConsole.MarkupLine("[bold greenyellow]You will into a very hard practice: 3 seconds[/]");
                        Thread.Sleep(1000);
                        Console.Clear();
                        AnsiConsole.MarkupLine("[bold yellow]You will into a very hard practice: 2 seconds[/]");
                        Thread.Sleep(1000);
                        Console.Clear();
                        AnsiConsole.MarkupLine("[bold orange1]You will into a very hard practice: 1 seconds!![/]");
                        Thread.Sleep(1000);
                        Console.Clear();
                        practice.Invoke();
                        break;
                }
                var confirm = AnsiConsole.Prompt(
                    new TextPrompt<bool>(PublicVariables.i18nStringsTable[PublicVariables.selectedCulture]["try_again"])
                         .AddChoice(true)
                        .AddChoice(false)
                        .DefaultValue(true)
                        .WithConverter(choice => choice ? "y" : "n")
                        .ChoicesStyle("chartreuse1")
                        .DefaultValueStyle("greenyellow bold"));
                if (!confirm) {
                    break;
                }
            }
        }
    }
}
