Initial requirement: Record books with title and publishing date.
```csharp
class Book {
  public string Title {get; private set;} = string.Empty;
  public DateOnly PublishingDate {get; private set;} = DateOnly.FromDateTime(DateTime.Today);
}
```

Requirement update: What about books which are yet to be published?
```csharp
class Book {
  public string Title {get; private set;} = string.Empty;
  public DateOnly PublishingDate {get; private set;} = DateOnly.FromDateTime(DateTime.Today);
  public bool IsPublished {get; private set;} = false;
}
```

Adding a boolean for this is bad design. Better design (but not great) would be to specify unpublished books as derived from books:
```csharp
class Book {
  public string Title {get; private set;} = string.Empty;
  public DateOnly PublishingDate {get; private set;} = DateOnly.FromDateTime(DateTime.Today);

  public override string ToString() =>
    $"{Title} published on {PublishingDate}";
}

class PlannedBook : Book {
  public override string ToString() =>
    $"{Title} planned for {PublishingDate}";
}
```

Deriving like this is very confusing because `PublishingDate` doesn't describe a planned publishing date. It is a missuse of derivation. To make this less ambiguos, lets seperate Planned from Published books, that are both derived from Book.
```csharp
abstract class Book {
  public string Title {get; private set;} = string.Empty; 
}

class PublishedBook : Book {
  public DateOnly PublishingDate {get; private set;} = DateOnly.FromDateTime(DateTime.Today);
  public override string ToString() =>
    $"{Title} published on {PublishingDate}";
}
 
class PlannedBook : Book {
  public DateOnly PlannedPublishingDate {get; private set;} = DateOnly.FromDateTime(DateTime.Today);
  public override string ToString() =>
    $"{Title} planned for {PlannedPublishingDate}";
}
```

This abstract Book class is never used in our code so this is an abuse of derivation. This is still the best solution using class inheritance, but object composition is a more favourable method:
```csharp 
class Book {
  public string Title {get; private set;} = string.Empty; 
  public PublicationInfo {get; private set;} = new NotPublishedYet();

  public override string ToString() => $"{Title} {Publication}";
}

abstract record PublicationInfo;
record Published(DateOnly OnDate)    : PublicationInfo;
record Planned(DateOnly PlannedDate) : PublicationInfo;
record NotPublishedYet               : PublicationInfo;  
```

This is more similar to algebraic types seen in functional languages. For example in Haskell:
```haskell
data PublicationInfo = 
    Published { OnDate :: DateOnly }
  | Planned   { PlannedDate :: DateOnly }
  | NotYetPunlished
  deriving (Show)

data Book = Book {
    Title :: String,
    Publication :: PublicationInfo
  } deriving (Show)
```

Requirement update: Count individual books in a set.
```csharp 
class Book {
  public string Title {get; private set;} = string.Empty; 
  public PublicationInfo {get; private set;} = new NotPublishedYet();

  public static int CountPublished(IEnumerable<Book> books) {
    int count = 0;
    foreach (Book book in books) {
      if (book.Publication is Published) count++;
    }
    return count;
  }
  public override string ToString() => $"{Title} {Publication}";
}

abstract record PublicationInfo;
record Published(DateOnly OnDate)    : PublicationInfo;
record Planned(DateOnly PlannedDate) : PublicationInfo;
record NotPublishedYet               : PublicationInfo;  
```

An inexperienced C# programmer would just count each object in an enumerable by creating a static method, which is fine, but not very elegant when .NET easily provides LINQ to do this kind of thing. Creating the static method may seem like expanding Book class capability, but it is limited when compared to simply doing everything with an external LINQ command. If the requirements to a query on `books` changes, then the static method is much more rigid of an aproach.
```csharp
int publishedCount = books.Count(book => book.Publication is Published);

class Book {
  public string Title {get; private set;} = string.Empty; 
  public PublicationInfo {get; private set;} = new NotPublishedYet();
  public override string ToString() => $"{Title} {Publication}";
}

abstract record PublicationInfo;
record Published(DateOnly OnDate)    : PublicationInfo;
record Planned(DateOnly PlannedDate) : PublicationInfo;
record NotPublishedYet               : PublicationInfo;   
```

Requirement update: How do we schedule book publication for specific days? (avoid public holidays, weekeneds, etc.)

```csharp


class Publishing {
  public void Schedule(Book book, DateOnly date) {
    if (book.Publication is Published) return;
  }
}

interface ICalendar {
  DateOnly ToFirstWorkday(DateOnly date);
}

class RegularDaysCalandar : ICalandar {
  public DateOnly ToFirstWorkDay(DateOnly date)
    => date.DayOfWeek switch {
      DayOfWeek.Saturday => date.AddDays(2),
      DayOfWeek.Sunday => date.AddDays(1),
      _ => date
    };
}
```
