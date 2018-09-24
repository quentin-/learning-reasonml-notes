open NoteModel;
let component = ReasonReact.statelessComponent("Note");

let make = (~note, ~onChange, _children) => {
  ...component,
  render: _self =>
    <textarea
      key=note.id
      autoFocus=true
      value=note.text
      onChange=(e => onChange(ReactEvent.Form.target(e)##value))
    />,
};