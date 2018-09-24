[%bs.raw {|require('./NoteList.css')|}];

open NoteModel;
let component = ReasonReact.statelessComponent("NoteList");

let titlefy = note =>
  switch (note) {
  | "" => "empty"
  | x => String.length(x) > 20 ? String.sub(x, 0, 20) ++ "..." : x
  };

let make = (~notes: list(note), ~selectedNoteId, ~onNoteClick, _children) => {
  let renderNote = note => {
    let selected =
      switch (selectedNoteId) {
      | Some(x) => x == note.id
      | None => false
      };

    let className =
      ["NoteList-item", selected ? "NoteList-item--selected" : ""]
      |> String.concat(" ");

    <li key=note.id className onClick=(_ => onNoteClick(note.id))>
      (note.text |> titlefy |> ReasonReact.string)
    </li>;
  };

  {
    ...component,
    render: _self =>
      <ul className="NoteList">
        <ReactCSSTransitionGroup
          transitionName="NoteList-item"
          transitionEnterTimeout=150
          transitionLeaveTimeout=150>
          (
            notes |> List.map(renderNote) |> Array.of_list |> ReasonReact.array
          )
        </ReactCSSTransitionGroup>
      </ul>,
  };
};