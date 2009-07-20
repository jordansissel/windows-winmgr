//{{NO_DEPENDENCIES}}
// Microsoft Visual C++ generated include file.
// Used by app.rc

#define MAIN_XAML \
 "<Window xmlns=\"http://schemas.microsoft.com/winfx/2006/xaml/presentation\"" \
 "        xmlns:x=\"http://schemas.microsoft.com/winfx/2006/xaml\">" \
 "  <DockPanel>" \
 "    <TextBox DockPanel.Dock=\"Bottom\" Name=\"userinput\" />" \
 "    <ScrollViewer>" \
 "      <ListBox Name=\"results\">" \
 "        <ListBox.ItemTemplate>" \
 "          <DataTemplate>" \
 "            <DataTemplate.Resources>" \
 "              <Style TargetType=\"TextBlock\">" \
 "                <Setter Property=\"FontSize\" Value=\"14\"/>" \
 "                <Setter Property=\"HorizontalAlignment\" Value=\"Center\"/>" \
 "              </Style>" \
 "            </DataTemplate.Resources>" \
 "            <Grid>" \
 "              <StackPanel>" \
 "                <TextBlock Margin=\"3,0,3,7\" Text=\"{Binding Path=title}\"/>" \
 "              </StackPanel>" \
 "            </Grid>" \
 "          </DataTemplate>" \
 "        </ListBox.ItemTemplate>" \
 "      </ListBox>" \
 "    </ScrollViewer>" \
 "  </DockPanel>" \
 "</Window>"
