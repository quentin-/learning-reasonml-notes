[%bs.raw {|require('./App.css')|}];
open NoteModel;

[@bs.module] external uuid : unit => string = "";

type notes = list(note);

type action =
  | CreateNote(string)
  | SelectNote(string)
  | DestroyNote(string)
  | UpdateNote(string, string);

type state = {
  notes,
  selectedNoteId: option(string),
};

let component = ReasonReact.reducerComponent("App");

let rec findIndex = f =>
  fun
  | [] => raise(Not_found)
  | [h, ...l] => f(h) ? 0 : 1 + findIndex(f, l);

let make = _ => {
  ...component,
  initialState: () => {notes: [], selectedNoteId: None},
  reducer: (action, state) =>
    switch (action) {
    | SelectNote(id) =>
      ReasonReact.Update({...state, selectedNoteId: Some(id)})
    | CreateNote(text) =>
      let id = uuid();
      ReasonReact.Update({
        selectedNoteId: Some(id),
        notes: [{id, text}, ...state.notes],
      });
    | UpdateNote(id, text) =>
      ReasonReact.Update({
        ...state,
        notes:
          state.notes
          |> List.map(note => note.id === id ? {...note, text} : note),
      })
    | DestroyNote(id) =>
      let index =
        switch (findIndex(n => n.id == id, state.notes)) {
        | exception Not_found => (-1)
        | x => x
        };

      let notes = state.notes |> List.filter(n => n.id != id);
      let nextNoteIndex = min(List.length(notes) - 1, index);

      let nextSelectedNoteId =
        List.length(notes) > 0 ?
          Some(List.nth(notes, nextNoteIndex).id) : None;

      ReasonReact.Update({notes, selectedNoteId: nextSelectedNoteId});
    },
  render: self => {
    let note =
      switch (self.state.selectedNoteId) {
      | None => None
      | Some(x) =>
        switch (List.find(note => note.id === x, self.state.notes)) {
        | note => Some(note)
        | exception Not_found => None
        }
      };

    <div className="app">
      <div className="app-header">
        <Button onClick=(_event => self.send(CreateNote("")))>
          (ReasonReact.string("Create"))
        </Button>
        (
          switch (self.state.selectedNoteId) {
          | None => ReasonReact.null
          | Some(x) =>
            <Button onClick=(_ => self.send(DestroyNote(x)))>
              (ReasonReact.string("Delete"))
            </Button>
          }
        )
      </div>
      <div className="app-notes">
        <div className="app-notes-list">
          <NoteList
            notes=self.state.notes
            selectedNoteId=self.state.selectedNoteId
            onNoteClick=(id => self.send(SelectNote(id)))
          />
        </div>
        <div className="app-notes-content">
          (
            switch (note) {
            | None => <div className="app-notes-content-empty" />
            | Some(n) =>
              <Note
                note=n
                onChange=(
                  v =>
                    String.length(v) == 0 ?
                      self.send(DestroyNote(n.id)) :
                      self.send(UpdateNote(n.id, v))
                )
              />
            }
          )
        </div>
      </div>
    </div>;
  },
};